#ifndef ShaderParametersBlock_h__
#define ShaderParametersBlock_h__

#include "Shader.h"
#include <vector>
#include <stdint.h>
#include <d3dcompiler.h>
#include "ForwardDeclarations.h"
#include "d3d11_types.h"

class ShaderBufferVariable {
public:
	std::string name;
	uint32_t offset;
	uint32_t size;

	ShaderBufferVariable() {

	}

	ShaderBufferVariable(const std::string& _name, uint32_t _offset, uint32_t _size)
		:name(_name), size(_size), offset(_offset){

	}
};

class ShaderResourceVariable {
public:
	std::string name;
	uint32_t bindPoint;
	D3D_SHADER_INPUT_TYPE type;
};

class ShaderBufferContext {
public:
	ID3D12ResourcePtr buffer;
	size_t size;
	std::vector<ShaderBufferVariable> variables;
	std::string name;
	uint32_t bindPoint;
	D3D_SHADER_INPUT_TYPE type;
};

class ShaderParametersContext {
public:
	void Clear() {
		buffers.clear();
		resources.clear();
	}
	std::vector<ShaderBufferContext> buffers;
	std::vector<ShaderResourceVariable> resources;
};

class ShaderParameter {
public:
	virtual ~ShaderParameter()
	{
	}

	ShaderParameter(const std::string& _name) :name(_name) {

	}
	virtual void* GetPointer() = 0;
	std::string name;
};

typedef std::shared_ptr<ShaderParameter> ShaderParameterPtr;

template<typename T>
class ShaderValueParameter : public ShaderParameter {
public:
	ShaderValueParameter(const std::string& _name) :ShaderParameter(_name)
	{

	}
	void* GetPointer() override {
		return &value;
	}
	T value;
};

class ShaderResourceParameter : public ShaderParameter {
public:
	ShaderResourceParameter(const std::string& _name) :ShaderParameter(_name) {

	}
	ShaderResourceParameter(const std::string& _name, ID3D11ShaderResourceViewPtr view) : value(view), ShaderParameter(_name) {
		name = _name;
	}
	ID3D11ShaderResourceViewPtr value;
	void* GetPointer() override {
		return nullptr;
	}
};

class ShaderTextureParameter : public ShaderParameter {
public:
	ShaderTextureParameter(const std::string& _name) :ShaderParameter(_name) {

	}
	ShaderTextureParameter(const std::string& _name, TexturePtr view) : ShaderParameter(_name), value(view){
		name = _name;
	}
	TexturePtr value;
	void* GetPointer() override {
		return nullptr;
	}
};

typedef std::shared_ptr<ShaderResourceParameter> ShaderResourceParameterPtr;
typedef std::shared_ptr<ShaderTextureParameter> ShaderTextureParameterPtr;

class ShaderParametersBlock {
public:
	void SetTexture(const std::string& name, TexturePtr texture) {
		/*ID3D11ResourcePtr resourcePtr;

		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);
		texture.QueryInterface(&resourcePtr);
		SetShaderResource(name, resourcePtr);*/

		ShaderTextureParameterPtr parameter(new ShaderTextureParameter(name, texture));
		for (auto it = parameters.begin(); it != parameters.end(); ++it) {
			if ((*it)->name == name) {
				*it = parameter;
				return;
			}
		}
		parameters.push_back(parameter);

	}

	template<typename T>
	void SetValue(const std::string& name, const T& value) {
		std::shared_ptr<ShaderValueParameter<T>> param(new ShaderValueParameter<T>(name));
		param->value = value;
		for (auto it = parameters.begin(); it != parameters.end(); ++it) {
			if ((*it)->name == name) {
				*it = param;
				return;
			}
		}
		parameters.push_back(param);
	}

	ShaderParameterPtr GetParameterByName(const std::string& name) {
		for (auto p : parameters) {
			if (p->name == name) {
				return p;
			}
		}
		return nullptr;
	}
private:
	std::vector<ShaderParameterPtr> parameters;
};

#endif // ShaderParametersBlock_h__
