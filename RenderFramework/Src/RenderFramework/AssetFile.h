#ifndef AssetFile_h__
#define AssetFile_h__

#include "InputArchive.h"
#include "OutputArchive.h"
#include "Asset.h"
#include <vector>
#include <sstream>
#include <filesystem>

namespace fs = std::experimental::filesystem::v1;

class AssetObjectDescriptor : public Object {
public:
	uint64_t localId;
	int64_t offset;
	uint64_t length;
	AssetObjectDescriptor():localId(0), offset(0), length(0)
	{
		
	}
	AssetObjectDescriptor(uint64_t _localId, int64_t _offset, uint64_t _length):localId(_localId), offset(_offset), length(_length){
		
	}
	virtual void serialize(Archive& archive) override {
		archive << localId << offset << length;
	}
	virtual std::wstring get_type_name() const override {
		return L"AssetObjectDescriptor";
	}
};

class AssetObjectsTable : public Object{
public:
	uint64_t lastId;
	std::vector<AssetObjectDescriptor> objects;

	AssetObjectsTable():lastId(0)
	{
		
	}

	bool GetFileDescriptor(uint64_t localId, AssetObjectDescriptor& desc){
		for (auto& o : objects) {
			if (o.localId == localId) {
				desc = o;
				return true;
			}
		}
		return false;
	}

	bool Contains(uint64_t localId) const {
		for (auto& o : objects) {
			if (o.localId == localId) {
				return true;
			}
		}
		return false;
	}

	virtual void serialize(Archive& archive) override {
		archive << lastId;
		if(archive.is_loading()){
			uint64_t objectsCount = 0;
			archive << objectsCount;
			objects.clear();
			for(uint64_t i = 0; i < objectsCount; ++i){
				AssetObjectDescriptor d;
				d.serialize(archive);
				objects.push_back(d);
			}
		}else{
			uint64_t objectsCount = objects.size();
			archive << objectsCount;
			for (auto& o : objects){
				o.serialize(archive);
			}
		}
	}
	virtual std::wstring get_type_name() const override {
		return L"AssetObjectsTable";
	}
};

inline std::shared_ptr<OutputArchive> CreateMemoryOutArchive(){
	return std::make_shared<OutputArchive>(std::make_shared<std::stringstream>(std::ios::in | std::ios::out | std::ios::binary));
}

class AssetFile {
public:
	typedef uint64_t table_offset_t;
	AssetObjectsTable objectsTable;
	std::shared_ptr<InputArchive> input;
	std::shared_ptr<OutputArchive> output;
	std::shared_ptr<std::fstream> stream;

	AssetFile(Guid fileGuid, const std::wstring& path):_fileGuid(fileGuid), _path(path){
		OpenFile(false);
		
		if(stream->is_open()){
			stream->seekg(0, std::ios::end);
			if((int)stream->tellg() == 0){
				std::cout << "Empty asset created!" << std::endl;
				SaveFooter();
			}
			ReadFooter();
		}
		//input = std::make_shared<InputArchive>(path);
	}

	void OpenFile(bool trunc){
		input = nullptr;
		output = nullptr;
		stream = std::make_shared<std::fstream>(_path, (trunc ? std::ios::trunc : std::ios::app) | std::ios::in | std::ios::out | std::ios::binary);
		if (stream->is_open()) {
			input = std::make_shared<InputArchive>(stream);
			output = std::make_shared<OutputArchive>(stream);
		}
	}

	void CloseFile()
	{
		input = nullptr;
		output = nullptr;
		if(stream != nullptr && stream->is_open()){
			stream->close();
		}
		stream = nullptr;
	}

	void Save(){
		auto tmpOut = CreateMemoryOutArchive();
		//save objects
		int64_t objectOffset = 0;
		for(auto& v : objectsTable.objects){
			auto object = Object::Find(AssetFileLink(_fileGuid, v.localId));

			v.offset = objectOffset;

			auto startOffset = objectOffset = tmpOut->GetStream()->tellp();
			//save all loaded objects, copy not loaded
			if(object != nullptr){
				auto typeName = object->get_type_name();
				(*tmpOut) << typeName;
				object->serialize(*tmpOut);
			}else{
				stream->seekg(v.offset, std::ios::beg);
				std::vector<uint8_t> objectBytes(v.length);
				stream->read((char*)&objectBytes[0], objectBytes.size());
				tmpOut->GetStream()->write((char*)&objectBytes[0], objectBytes.size());
			}
			objectOffset = tmpOut->GetStream()->tellp();
			v.length = objectOffset - startOffset;
		}

		CloseFile();
		OpenFile(true);

		auto content = std::static_pointer_cast<std::stringstream>(tmpOut->GetStream())->str();
		stream->write(&content[0], content.size());
		stream->seekg(0, std::ios::end);
		//save footer
		SaveFooter();
	}

	bool SeekToFile(uint64_t fileId) {
		AssetObjectDescriptor desc;
		if (objectsTable.GetFileDescriptor(fileId, desc)) {
			if (desc.offset >= 0) {
				stream->seekg(desc.offset, std::ios::beg);
				return true;
			}
		}
		return false;
	}

	void ReadFooter()
	{
		std::cout << "Read footer" << std::endl;
		//read table offset
		auto off = -((std::streamoff)sizeof(table_offset_t));
		stream->seekg(off, std::ios::end);
		table_offset_t offset = 0;
		(*input) << offset;

		auto table_file_offset = off - (std::streamoff)offset;
		stream->seekg(table_file_offset, std::ios::end);
		objectsTable.serialize(*input);
	}

	void SaveFooter(){
		std::cout << "Save footer" << std::endl;
		stream->seekg(0, std::ios::end);
		auto tmpArchive = CreateMemoryOutArchive();
		objectsTable.serialize(*tmpArchive);
		auto data = std::static_pointer_cast<std::stringstream>(tmpArchive->GetStream())->str();
		table_offset_t size = data.size();
		stream->write(&data[0], size);
		(*output) << size;

		output->flush();
	}

	void AddObject(std::shared_ptr<Object> obj){
		if (obj->GetFileLink().IsValid()) {
			if (obj->GetFileLink().fileGuid == _fileGuid) {
				std::wcout << "Object " << obj->get_name() << " is already in current asset. Can't add twice" << std::endl;
			} else {
				std::wcout << "Object " << obj->get_name() << " is already in another asset. Can't add." << std::endl;
			}
		} else {
			obj->SetLink(AssetFileLink(_fileGuid, objectsTable.lastId++));
			objectsTable.objects.push_back(AssetObjectDescriptor(obj->GetFileLink().localId, 0, 0));
		}
	}
	const Guid& guid() const
	{
		return _fileGuid;
	}
private:
	Guid _fileGuid;
	std::wstring _path;
};

#endif // AssetFile_h__
