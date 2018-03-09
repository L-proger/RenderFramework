#ifndef Material_h__
#define Material_h__

#include "Shader.h"
#include <vector>
#include <stdint.h>
#include <d3dcompiler.h>
#include "ForwardDeclarations.h"
#include "ShaderParametersBlock.h"
#include "Object.h"

#include <wrl.h>

using namespace Microsoft::WRL;

class Material : public Object {
public:
	std::wstring class_name() const {
		return L"Material";
	}
	void SetShader(ShaderPtr _shader);
	ShaderPtr GetShader() {
		return shader;
	}
	void SetParametersBlock(ShaderParametersBlock& block);
	ShaderParametersBlock& GetParametersBlock() {
		return parameters;
	}
	void Apply();
	static MaterialPtr Create(std::string name);
	static MaterialPtr Create(ShaderPtr shader, std::string name);
	static std::string DiffuseMapName();
	static std::string NormalMapName();
	static std::string DiffuseColorName();
	ShaderParametersContext& GetCompiledParameters(ShaderType shader_type)
	{
		return shaderParameters[(uint32_t)shader_type];
	}
private:

	Material(std::string name) 
		:_name(name)
	{

	}
	std::string _name;
	ShaderPtr shader;
	ShaderParametersContext shaderParameters[(uint32_t)ShaderType::Count];
	ShaderParametersBlock parameters;


	void RebuildBuffers();
	void RebuildShaderParameters(ShaderParametersContext& params, ComPtr<ID3D12ShaderReflection> reflection);
};


#endif // Material_h__
