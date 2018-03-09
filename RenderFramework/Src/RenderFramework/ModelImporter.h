#ifndef ModelImporter_h__
#define ModelImporter_h__

#include "AssetImporter.h"
#include <filesystem>
#include <vector>
#include <string>
#include "ObjMeshLoader.h"
#include "AssetDatabase.h"

class ModelImporter : public AssetImporter {
public:
	virtual bool can_import(const std::wstring& path) const override {
		std::experimental::filesystem::path src_path(path);
		return src_path.extension() == ".obj";
	}

	virtual std::wstring name() override {
		return L"ModelImporter";
	}

	virtual bool set_parameters(std::wstring params) override {
		return false;
	}

	virtual std::wstring get_parameters() const override {
		return L"";
	}

	virtual void import(std::wstring asset_path) override {
		ObjMeshLoader loader;
		loader.Load(asset_path);
	}

};
#endif // ModelImporter_h__
