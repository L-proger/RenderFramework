#pragma once

#include <d3dcommon.h>
#include <vector>
#include <cstdint>
#include <string>
#include <codecvt>
#include <locale>
#include "File.h"
#include <memory>
#include <stack>
#include <filesystem>

namespace fs = std::experimental::filesystem::v1;

class ShaderIncludeFile {
public:
	std::wstring fullPath;
	std::vector<char> data;
};

class ShaderInclude : public ID3DInclude {
public:
	ShaderInclude(std::wstring localDirectory){
		_localPathStack.push(localDirectory);
	}

	STDOVERRIDEMETHODIMP Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes){
		std::wstring wideFileName = std::wstring(pFileName, pFileName + strlen(pFileName));

		std::wstring fullPath;

		switch (IncludeType) {
		case D3D_INCLUDE_LOCAL:
		case D3D_INCLUDE_SYSTEM:
			fullPath = _localPathStack.top() + L"/" + wideFileName;

			fs::path p(fullPath);
			auto parent = p.parent_path();
			_localPathStack.push(parent.wstring());
			break;
		}

		for (auto& f : _files) {
			if (f->fullPath == fullPath) {
				throw std::exception("Circular dependency detected!");
			}
		}

		auto file = std::make_shared<ShaderIncludeFile>();
		file->fullPath = fullPath;
		FileReadAllBytes(fullPath, file->data);
		_files.push_back(file);

		*ppData = &file->data[0];
		*pBytes = file->data.size();
		return S_OK;
	}

	STDOVERRIDEMETHODIMP Close(THIS_ LPCVOID pData){
		_localPathStack.pop();
		return S_OK;
	}

private:
	std::stack<std::wstring> _localPathStack;
	std::vector<std::shared_ptr<ShaderIncludeFile>> _files;
};
