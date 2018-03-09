#include "Shader.h"
#include <d3dcompiler.h>
#include <fstream>
#include "File.h"
#include "LEngine.h"
#include "AssetManager.h"
#include "ShaderInclude.h"
#include <filesystem>

#pragma comment(lib, "D3dcompiler.lib")

namespace fs = std::experimental::filesystem::v1;

ComPtr<ID3DBlob> Shader::CompileSHader(const std::wstring& filename, const std::string& entry, const std::string& profile) {
	std::ifstream file(filename);
	if(!file.good()) {
		return nullptr;
	}

	fs::path p(filename);
	auto parent = p.parent_path();

	ShaderInclude inc(parent.wstring());

	std::string shaderCode;
	FileReadAllText(filename, shaderCode);

	ComPtr<ID3DBlob> blob;
	ComPtr<ID3DBlob> errorBlob;

	//compile vertex shader
	if(S_OK != D3DCompile(shaderCode.c_str(), shaderCode.size(), "", nullptr, &inc, entry.c_str(), profile.c_str(), D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, &errorBlob)) {
		char* ptr = (char*)errorBlob->GetBufferPointer();
		throw std::exception((char*)errorBlob->GetBufferPointer());
		return nullptr;
	}
	return blob;
}

Shader::Shader(ComPtr<ID3D12Device> dev) :device(dev) {

}

ShaderPtr Shader::Create() {
	return std::shared_ptr<Shader>(new Shader(LEngine::Instance()->GetRenderer()->GetDevice()));
}

ShaderPtr Shader::Create(const std::wstring& filePath) {
	auto shader = Create();
	shader->FromFile(AssetManager::Instance()->GetFullAssetPath(filePath));
	return shader;
}

void Shader::FromFile(const std::wstring& shaderFilePath) {
	auto vsBlob = CompileSHader(shaderFilePath, "main_vs", "vs_5_0");
	if(vsBlob != nullptr) {
		ShaderDataPtr shader(new ShaderData());
		shader->blob = vsBlob;
		shaders[(int)ShaderType::Vs] = shader;
	}
	
	auto psBlob = CompileSHader(shaderFilePath, "main_ps", "ps_5_0");
	if(psBlob != nullptr) {
		ShaderDataPtr shader(new ShaderData());
		shader->blob = psBlob;
		shaders[(int)ShaderType::Ps] = shader;
	}
}

ShaderDataPtr Shader::GetShader(ShaderType type) {
	return shaders[(uint32_t)type];
}

ComPtr<ID3D12Device> Shader::GetDevice() {
	return device;
}