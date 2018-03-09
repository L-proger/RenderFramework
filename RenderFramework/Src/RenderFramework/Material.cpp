#include "Material.h"
#include <d3d11.h>
#include <stdint.h>
#include <NativeLINQ/NativeLINQ.h>
#include <cassert>
#include <cstring>
#include "d3dx12.h"
#include "FatalError.h"

void Material::SetShader(ShaderPtr _shader) {
	shader = _shader;
	RebuildBuffers();
}

std::string Material::DiffuseMapName() {
	return "_DiffuseMap";
}
std::string Material::NormalMapName() {
	return "_NormalMap";
}
std::string Material::DiffuseColorName() {
	return "_DiffuseColor";
}
MaterialPtr Material::Create(std::string name) {
	return std::shared_ptr<Material>(new Material(name));
}

MaterialPtr Material::Create(ShaderPtr shader, std::string name) {
	auto material = Create(name);
	material->SetShader(shader);
	return material;
}

void Material::Apply() {
	for(int i = 0; i < (int)ShaderType::Count; ++i) {
		auto s = shader->GetShader((ShaderType)i);
		if(s != nullptr) {

			//apply shaders
			//s->Apply(context);

			auto& p = shaderParameters[i];
			//update and apply buffers
			for (auto& bufferCtx : p.buffers) {

				D3D12_RANGE range;
				range.Begin = range.End = 0;

				uint8_t* data = nullptr;

				auto hr =  bufferCtx.buffer->Map(0, &range, (void**)&data);
				assert(hr == S_OK);

				//write all variables
				for (auto& variable : bufferCtx.variables) {
					auto param = parameters.GetParameterByName(variable.name);
					if (param != nullptr) {
						memcpy(data + variable.offset, param->GetPointer(), variable.size);
					}
				}

				range.End = bufferCtx.size;
				bufferCtx.buffer->Unmap(0, &range);
				assert(hr == S_OK);
				/*context->Unmap(bufferCtx.buffer, 0);
				ID3D11Buffer* buffers[1] = { bufferCtx.buffer };

				switch ((ShaderType)i)
				{
				case ShaderType::Vs:
					context->VSSetConstantBuffers(bufferCtx.bindPoint, 1, buffers);
					break;
				case ShaderType::Ps:
					context->PSSetConstantBuffers(bufferCtx.bindPoint, 1, buffers);
					break;
				default:
					assert(false && "not implemented");
				}*/

				//sr.pData

			}

			//apply shader resources
			/*for (auto& resourceCtx : p.resources) {
				auto param = parameters.GetParameterByName(resourceCtx.name);
				if (param != nullptr) {
					auto resourceParam = std::dynamic_pointer_cast<ShaderResourceParameter>(param);

					ID3D11ShaderResourceView* resources[1] = { resourceParam->value };

					switch ((ShaderType)i)
					{
					case ShaderType::Vs:
						context->VSSetShaderResources(resourceCtx.bindPoint, 1, resources);
						break;
					case ShaderType::Ps:
						context->PSSetShaderResources(resourceCtx.bindPoint, 1, resources);
						break;
					default:
						assert(false && "not implemented");
					}
				}
				
			}*/
				
		} else {

		}
	}
}

void Material::RebuildShaderParameters(ShaderParametersContext& params, ComPtr<ID3D12ShaderReflection> reflection) {
	

	D3D12_SHADER_DESC d;
	reflection->GetDesc(&d);

	params.Clear();

	//get resource variables
	for(uint32_t i = 0; i < d.BoundResources; ++i) {
		D3D12_SHADER_INPUT_BIND_DESC bindDesc;
		reflection->GetResourceBindingDesc(i, &bindDesc);

		ShaderResourceVariable var;
		var.bindPoint = bindDesc.BindPoint;
		var.name = bindDesc.Name;
		var.type = bindDesc.Type;
		params.resources.push_back(var);
	}


	//get constant buffers
	for(uint32_t i = 0; i < d.ConstantBuffers; ++i) {
		ShaderBufferContext ctx;
		ID3D12ShaderReflectionConstantBuffer* cb = reflection->GetConstantBufferByIndex(i);

		auto device = shader->GetDevice();
		D3D12_SHADER_BUFFER_DESC bufferDesc;
		cb->GetDesc(&bufferDesc);

		ctx.name = bufferDesc.Name;

		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = bufferDesc.Size;
		cbDesc.Usage = D3D11_USAGE_DYNAMIC;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;


		auto hr = device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // this heap will be used to upload the constant buffer data
			D3D12_HEAP_FLAG_NONE, // no flags
			&CD3DX12_RESOURCE_DESC::Buffer(1024 * 64), // Must be a multiple of 64KB for single-textures and constant buffers.  TODO: handle size overflow o_O  Maybe.
			D3D12_RESOURCE_STATE_GENERIC_READ, 
			nullptr,
			IID_PPV_ARGS(&ctx.buffer));

		ctx.buffer->SetName(L"Constant Buffer Upload Resource Heap");


		//device->CreateBuffer(&cbDesc, nullptr, &ctx.buffer);

		for(uint32_t j = 0; j < bufferDesc.Variables; ++j) {
			auto variable = cb->GetVariableByIndex(j);
			D3D12_SHADER_VARIABLE_DESC varDesc;
			variable->GetDesc(&varDesc);
			ctx.variables.push_back(ShaderBufferVariable(varDesc.Name, varDesc.StartOffset, varDesc.Size));
		}

		//find buffer's bind point

		auto res = Where(params.resources, [ctx](ShaderResourceVariable srv) {return srv.name == ctx.name && srv.type == D3D_SIT_CBUFFER; })->ToVector();
		ctx.bindPoint = res[0].bindPoint;
		ctx.type = res[0].type;
		ctx.size = cbDesc.ByteWidth;
		params.buffers.push_back(ctx);
	}
}

void Material::RebuildBuffers() {
	ComPtr<ID3D12ShaderReflection> reflection;
	for(int i = 0; i < (int)ShaderType::Count; ++i) {
		auto vs = shader->GetShader((ShaderType)i);
		if(vs != nullptr) {
			reflection = nullptr;
			D3DReflect(vs->blob->GetBufferPointer(), vs->blob->GetBufferSize(), __uuidof(reflection), (void**)&reflection);
			RebuildShaderParameters(shaderParameters[i], reflection);
		}
	}
}

void Material::SetParametersBlock(ShaderParametersBlock& block) {
	parameters = block;
}