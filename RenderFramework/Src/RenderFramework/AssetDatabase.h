#ifndef AssetDatabase_h__
#define AssetDatabase_h__

#include <string>
#include <memory>
#include <vector>

#include "AssetMetadata.h"
#include "AssetImporter.h"
#include "AssetFile.h"


class AssetDatabase{
public:
	static AssetDatabase& get() {
		static AssetDatabase instance;
		return instance;
	}
	static std::wstring asset_to_meta_path(const std::wstring& asset_path);
	Guid file_to_guid(const std::wstring& path) const;
	std::shared_ptr<AssetFile> open_asset_file(const std::wstring& path);
	void set_root_path(const std::wstring& path);
	static void register_importer(std::shared_ptr<AssetImporter> importer);
	std::shared_ptr<AssetImporter> find_importer(const std::wstring& asset_path) const;

	std::shared_ptr<Object> LoadReference(const AssetFileLink& link);
	std::shared_ptr<AssetFile> OpenArchive(Guid guid);
	std::shared_ptr<Object> LoadObject(AssetFileLink link);

	std::vector<std::shared_ptr<Object>> load_all_objects(std::shared_ptr<AssetFile> asset);
private:
	std::vector<std::shared_ptr<AssetFile>> open_archives;
	AssetDatabase();
	std::vector<std::shared_ptr<AssetImporter>> _importers;
};
#endif // AssetDatabase_h__
