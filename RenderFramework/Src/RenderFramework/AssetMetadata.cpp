#include "AssetMetadata.h"
#include <fstream>
#include <combaseapi.h>
#include <iostream>
#include <string>
#include <sstream>
#include "AssetDatabase.h"
#include <Windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

AssetMetadata::AssetMetadata(const std::wstring& asset_path) : _asset_path(asset_path) {
	_meta_path = AssetDatabase::asset_to_meta_path(_asset_path);

	if (std::experimental::filesystem::exists(std::experimental::filesystem::path(_meta_path))) {
		Load();
	} else {
		create();
		Save();
	}
}

void AssetMetadata::create() {
	CoCreateGuid((GUID*)&_guid);
	_modification_time = std::experimental::filesystem::last_write_time(std::experimental::filesystem::path(_asset_path)).time_since_epoch().count();
	_importer = AssetDatabase::get().find_importer(_asset_path);
}

void AssetMetadata::Load() {
	std::wifstream file(_meta_path);

	std::wstring v;
	std::getline(file, v);

	std::wstring guid_str;
	std::getline(file, guid_str);
	_guid = str_to_guid(guid_str);

	std::wstring time_str;
	std::getline(file, time_str);
	_modification_time = std::stoull(time_str);

	file.close();
}

void AssetMetadata::Save() {
	std::wofstream file;
	file.open(_meta_path, std::ios::trunc);
	file << version << std::endl;
	file << guid_to_str(_guid) << std::endl;
	file << _modification_time << std::endl;
	//file << _importer->name();
	file.close();
}

Guid AssetMetadata::str_to_guid(const std::wstring& guid) {
	Guid iid;
	IIDFromString(guid.c_str(), (GUID*)&iid);
	return iid;
}

std::wstring AssetMetadata::guid_to_str(const Guid& guid) {
	LPOLESTR guid_str = nullptr;
	StringFromIID(*((const GUID*)&guid), &guid_str);

	//Microsoft::WRL::Wrappers::HStringReference

	std::wstring result(guid_str);
	CoTaskMemFree(guid_str);
	return result;
}

const Guid& AssetMetadata::get_guid() const {
	return _guid;
}