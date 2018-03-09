#include "AssetDatabase.h"
#include <filesystem>
#include <iostream>
#include "ModelImporter.h"
#include "TextureImporter.h"
#include <algorithm>

AssetDatabase::AssetDatabase()
{
	_importers.push_back(std::make_shared<ModelImporter>());
	//_importers.push_back(std::make_shared<TextureImporter>());
}

void AssetDatabase::set_root_path(const std::wstring& path)
{
}

std::wstring AssetDatabase::asset_to_meta_path(const std::wstring& asset_path)
{
	std::experimental::filesystem::path src(asset_path);
	return src.parent_path().append(src.filename().wstring() + L".meta").wstring();
}

void AssetDatabase::register_importer(std::shared_ptr<AssetImporter> importer)
{
}

std::vector<std::shared_ptr<Object>> AssetDatabase::load_all_objects(std::shared_ptr<AssetFile> asset)
{
	std::vector<std::shared_ptr<Object>> result;
	auto table = asset->objectsTable;
	for (auto& obj : table.objects)
	{
		result.push_back(LoadObject(AssetFileLink(asset->guid(), obj.localId)));
	}
	return result;
}


std::shared_ptr<AssetImporter> AssetDatabase::find_importer(const std::wstring& asset_path) const
{
	auto importer = std::find_if(_importers.begin(), _importers.end(), [asset_path](std::shared_ptr<AssetImporter> im) { return im->can_import(asset_path); });
	if (importer != _importers.end())
	{
		return *importer;
	}
	return nullptr;
}

Guid AssetDatabase::file_to_guid(const std::wstring& path) const
{
	return AssetMetadata(path).get_guid();
}

std::shared_ptr<AssetFile> AssetDatabase::open_asset_file(const std::wstring& path)
{
	return std::make_shared<AssetFile>(file_to_guid(path), path);
}

std::shared_ptr<Object> AssetDatabase::LoadReference(const AssetFileLink& link)
{
	return LoadObject(link);
}


std::wstring guid_to_path(Guid guid)
{//TODO: fix hardcode
	return LR"(C:\Users\Sergey\Desktop\Assets\test.asset)";
}


std::shared_ptr<AssetFile> AssetDatabase::OpenArchive(Guid guid)
{ //TODO: fix hardcode
	if (open_archives.empty())
	{
		auto a = std::make_shared<AssetFile>(guid, guid_to_path(guid));
		a->input->LoadReferenceCallback = std::bind(&AssetDatabase::LoadReference, this, std::placeholders::_1);
		open_archives.push_back(a);
	}
	return open_archives[0];
}

std::shared_ptr<Object> AssetDatabase::LoadObject(AssetFileLink link)
{
	auto f = Object::Find(link);
	if (f != nullptr) { return f; }

	auto archive = OpenArchive(link.fileGuid);
	archive->SeekToFile(link.localId);

	std::wstring type_name;
	(*archive->input) << type_name;

	auto obj = ObjectsFactory::instance().create_object(type_name);
	obj->SetLink(link);

	obj->serialize(*archive->input);


	return obj;
}
