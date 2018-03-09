#pragma once

#include <memory>
#include <string>
#include "d3d11_types.h"
#include "Texture.h"
#include "ForwardDeclarations.h"

class AssetManager {
public:
	static std::shared_ptr<AssetManager> Instance() {
		if (_instance == nullptr) {
			_instance = std::make_shared<AssetManager>();
		}
		return _instance;
	}

	void SetAssetsFolder(const std::wstring& folder) {
		_assetsFolder = folder;
	}

	std::wstring GetFullAssetPath(const std::wstring& relativePath) const
	{
		return _assetsFolder + relativePath;
	}
	TexturePtr LoadTexture(const std::wstring& path) const;
private:
	static std::shared_ptr<AssetManager> _instance;
	std::wstring _assetsFolder;
};
