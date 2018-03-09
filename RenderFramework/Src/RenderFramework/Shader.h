#ifndef Shader_h__
#define Shader_h__

#include <string>
#include <memory>
#include <cassert>
#include "ForwardDeclarations.h"
#include <d3d12.h>
#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class ShaderData {
public:
	ComPtr<ID3DBlob> blob;

	D3D12_SHADER_BYTECODE get_bytecode() {
		D3D12_SHADER_BYTECODE bytecode = {};
		bytecode.BytecodeLength = blob->GetBufferSize();
		bytecode.pShaderBytecode = blob->GetBufferPointer();
		return bytecode;
	}
};

typedef std::shared_ptr<ShaderData> ShaderDataPtr;

enum class ShaderType {
	Vs,
	Ps,
	Gs,
	Hull,
	Domain,
	Count
};

class Shader {
public:
	std::wstring class_name() const {
		return L"Shader";
	}
	static ShaderPtr Create();
	static ShaderPtr Create(const std::wstring& filePath);
	void FromFile(const std::wstring& shaderFilePath);
	ShaderDataPtr GetShader(ShaderType type);
	ComPtr<ID3D12Device> GetDevice();
private:
	Shader(ComPtr<ID3D12Device> dev);
	ShaderDataPtr shaders[(uint32_t)ShaderType::Count];
	ComPtr<ID3D12Device> device;
	ComPtr<ID3DBlob> CompileSHader(const std::wstring& filename, const std::string& entry, const std::string& profile);
};



#endif // Shader_h__
