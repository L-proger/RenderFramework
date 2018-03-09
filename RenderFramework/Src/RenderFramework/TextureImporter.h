#ifndef TextureImporter_h__
#define TextureImporter_h__

#include "AssetImporter.h"
#include <filesystem>

/*
class TextureImporter : public AssetImporter {
public:
	virtual bool can_import(const std::wstring& path) const override {
		std::tr2::sys::path file_path(path);
		if (!file_path.has_extension()) {
			return false;
		} else {
			return file_path.extension() == ".bmp";
		}
	}

	virtual bool load_parameters(const std::wstring& params) override {
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual std::wstring save_parameters() override {
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual std::wstring name() override {
		return L"TextureImporter";
	}

};*/

#endif // TextureImporter_h__
