#ifndef AssetImporter_h__
#define AssetImporter_h__

#include <string>
#include <vector>
#include <filesystem>

class AssetImporter {
public:
	virtual void import(std::wstring asset_path) = 0;
	virtual bool can_import(const std::wstring& path) const = 0;
	virtual bool set_parameters(std::wstring params) = 0;
	virtual std::wstring get_parameters() const = 0;
	virtual std::wstring name() = 0;
};
#endif // AssetImporter_h__
