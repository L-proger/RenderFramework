#ifndef AssetMetadata_h__
#define AssetMetadata_h__

#include <filesystem>
#include <cstdint>
#include <memory>
#include "Guid.h"
#include "AssetImporter.h"

class AssetMetadata {
public:
	typedef uint64_t file_time_t;
	const std::wstring version = L"1.0";

	AssetMetadata(const std::wstring& asset_path);
	void Save();
	void Load();
	static std::wstring guid_to_str(const Guid& guid);
	static Guid str_to_guid(const std::wstring& guid);
	const Guid& get_guid() const;
private:
	std::shared_ptr<AssetImporter> _importer;
	void create();
	std::wstring _asset_path;
	std::wstring _meta_path;
	file_time_t _modification_time;
	Guid _guid;
};
#endif // AssetMetadata_h__
