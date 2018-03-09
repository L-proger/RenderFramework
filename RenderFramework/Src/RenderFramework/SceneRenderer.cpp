#include "SceneRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"

SceneRenderer::SceneRenderer()
{
	auto renderer = LEngine::Instance()->GetRenderer();
	auto device = renderer->GetDevice();

	//create samplers heap
	D3D12_DESCRIPTOR_HEAP_DESC samplers_heap_desc;
	samplers_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	samplers_heap_desc.NodeMask = 0;
	samplers_heap_desc.NumDescriptors = 1;
	samplers_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
	HR_ASSERT(device->CreateDescriptorHeap(&samplers_heap_desc, IID_PPV_ARGS(&samplers_heap)));
	samplers_heap->SetName(L"Samplers heap");

	//create texture sampler
	D3D12_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D12_FLOAT32_MAX;
	sampler_desc.MipLODBias = 0.0f;
	sampler_desc.MaxAnisotropy = 1;
	sampler_desc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	renderer->GetDevice()->CreateSampler(&sampler_desc, samplers_heap->GetCPUDescriptorHandleForHeapStart());
}

void SceneRenderer::RenderScene(RendererPtr renderer, ScenePtr scene, CameraPtr camera, std::shared_ptr<RenderOutput> renderScreen) {
	camera->aspect = (float)renderScreen->GetWidth() / (float)renderScreen->GetHeight();
	renderScreen->OnPreRender(renderer);

	D3D12_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)renderScreen->GetWidth();
	viewport.Height = (float)renderScreen->GetHeight();
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;


	D3D12_RECT scissorRect = {};
	scissorRect.left = 0;
	scissorRect.top = 0;
	scissorRect.right = renderScreen->GetWidth();
	scissorRect.bottom = renderScreen->GetHeight();

	auto commandList = renderer->BeginCommandList();
	auto rt = renderScreen->GetRenderTarget(renderScreen->GetCurrentBufferIndex());
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(rt.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	auto rtvHandle = renderScreen->GetRenderTargetDescriptor(renderScreen->GetCurrentBufferIndex());
	auto dsvHandle = renderScreen->GetDepthStencilDescriptor(renderScreen->GetCurrentBufferIndex());
	commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

	const float clearColor[] = { 0.1f, 0.1f, 0.14f, 1.0f };
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	//renderer->EndCommandList();
//	renderer->WaitCommandsQueue();

	commandList->RSSetViewports(1, &viewport);
	commandList->RSSetScissorRects(1, &scissorRect);

	std::vector<ComPtr<ID3D12RootSignature>> signatures;
	std::vector<ComPtr<ID3D12PipelineState>> pso;

	
	//draw all objects
	for (auto obj : scene->objects) {
		auto mr = obj->GetComponent<MeshRenderer>();
		if (mr != nullptr) {
			auto mesh = mr->GetMesh();
			if (mesh != nullptr) {
				for (uint32_t i = 0; i < mesh->GetSubmeshCount(); ++i) {
					auto mat = mr->GetMaterials()[i];
					auto submesh = mesh->GetSubmeshes()[i];
					if (mat == nullptr || submesh == nullptr) {
						continue;
					}
					auto& params = mat->GetParametersBlock();

					//params.SetShaderResource()
					
					//set system variables
					auto tf = obj->transform->GetGlobalTransform();
					auto view = camera->worldToCameraMatrix();
					auto proj = camera->projectionMatrix();
					params.SetValue("mWorld", transpose(tf));
					params.SetValue("mView", transpose(view));
					params.SetValue("mProjection", transpose(proj));

					auto camPos = camera->transform()->GetGlobalPosition();
					params.SetValue("cameraWorldPos", float4(camPos.x(), camPos.y(), camPos.z(), 0.0f));

					mat->Apply();


					//create single element ranges for constant buffers
					std::vector<D3D12_ROOT_PARAMETER> root_parameters;

					auto compiled_params = mat->GetCompiledParameters(ShaderType::Vs);

					for(auto p : compiled_params.buffers)
					{
						D3D12_ROOT_DESCRIPTOR rootCBVDescriptor;
						rootCBVDescriptor.RegisterSpace = 0;
						rootCBVDescriptor.ShaderRegister = p.bindPoint;

						D3D12_ROOT_PARAMETER root_param = {};
						root_param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
						root_param.Descriptor = rootCBVDescriptor;

						root_parameters.push_back(root_param);
					}


					size_t srvParamOffset = root_parameters.size();
					size_t srvParamCount = 0;

					auto srvHeapAllocator = renderer->getSrvDescriptorsAllocator();
					auto srvHeap = srvHeapAllocator->getHeap();

					std::vector<D3D12_DESCRIPTOR_RANGE> srvRanges[2];
					//size_t srvParamCount = 
					//VS + PS
					for(int id = 0; id < 2; ++id){
						auto shader_params = mat->GetCompiledParameters((ShaderType)id);
				
						for(auto r : shader_params.resources){
							if(r.type == D3D_SIT_TEXTURE)
							{
								auto param = mat->GetParametersBlock().GetParameterByName(r.name);
								auto texParam = std::static_pointer_cast<ShaderTextureParameter>(param);
								auto tex = texParam == nullptr ? nullptr : texParam->value;

								D3D12_DESCRIPTOR_RANGE range{};
								range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
								range.RegisterSpace = 0;
								range.NumDescriptors = 1;
								range.BaseShaderRegister = r.bindPoint;
								range.OffsetInDescriptorsFromTableStart = srvHeapAllocator->getDescriptorId(tex->srvDescriptor);
								srvRanges[id].push_back(range);
							}
						}
					}

					//for each shader => create root table parameter
					for(size_t s = 0; s < 2; ++s)
					{
						auto& ranges = srvRanges[s];
						if(!ranges.empty())
						{
							D3D12_ROOT_DESCRIPTOR_TABLE srvTable;
							srvTable.NumDescriptorRanges = ranges.size();
							srvTable.pDescriptorRanges = &ranges[0];

							D3D12_ROOT_PARAMETER srvParameter;
							srvParameter.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
							srvParameter.ShaderVisibility = ((ShaderType)s == ShaderType::Vs) ? D3D12_SHADER_VISIBILITY_VERTEX : D3D12_SHADER_VISIBILITY_PIXEL;
							srvParameter.DescriptorTable = srvTable;
							root_parameters.push_back(srvParameter);

							srvParamCount++;
						}
					}


					// create a static sampler
					D3D12_STATIC_SAMPLER_DESC sampler = {};
					sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
					sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
					sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
					sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
					sampler.MipLODBias = 0;
					sampler.MaxAnisotropy = 0;
					sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
					sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
					sampler.MinLOD = 0.0f;
					sampler.MaxLOD = D3D12_FLOAT32_MAX;
					sampler.ShaderRegister = 0;
					sampler.RegisterSpace = 0;
					sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

					
					//create root signature
					CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
					rootSignatureDesc.Init(root_parameters.size(), // we have 1 root parameter
						&root_parameters[0], // a pointer to the beginning of our root parameters array
						1,
						&sampler,
						D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | // we can deny shader stages here for better performance
						D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
						D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
						D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS);


					ComPtr<ID3DBlob> signature;
					ComPtr<ID3DBlob> signatureErrors;
					auto hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &signatureErrors);
					if (FAILED(hr)) {
						FatalError(L"Failed to serialize root signature");
					}

					ComPtr<ID3D12RootSignature> rootSignature;
					hr = renderer->GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
					if (FAILED(hr)) {
						FatalError(L"Failed to create root signature");
					}

					signatures.push_back(rootSignature);


					//create PSO
					DXGI_SAMPLE_DESC sampleDesc = {};
					sampleDesc.Count = 1;
					
					D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
					psoDesc.pRootSignature = rootSignature.Get();
					psoDesc.InputLayout = mr->GetInputLayout();
					psoDesc.VS = mat->GetShader()->GetShader(ShaderType::Vs)->get_bytecode();
					psoDesc.PS = mat->GetShader()->GetShader(ShaderType::Ps)->get_bytecode();
					psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
					psoDesc.RTVFormats[0] = DXGI_FORMAT_B8G8R8A8_UNORM;
					psoDesc.SampleDesc = sampleDesc;
					psoDesc.SampleMask = 0xffffffff;
					psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
					psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
					psoDesc.NumRenderTargets = 1;
					psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
					psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

					auto device = renderer->GetDevice();

					
						if (FAILED(hr)) {
							FatalError(L"Failed to create PSO");
						}

						ComPtr<ID3D12PipelineState> pipelineStateObject;
						hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineStateObject));
						pipelineStateObject->SetName(L"PSO");


						pso.push_back(pipelineStateObject);


						//commandList = renderer->BeginCommandList();

						commandList->SetPipelineState(pipelineStateObject.Get());

						commandList->SetGraphicsRootSignature(rootSignature.Get());

						commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
						auto vbView = mesh->GetVertexBufferView();

						commandList->IASetVertexBuffers(0, 1, &vbView);

						auto ibView = submesh->GetIndexBufferView();
						commandList->IASetIndexBuffer(&ibView);

						//commandList->SetGraphicsRootShaderResourceView()


						ID3D12DescriptorHeap* descriptorHeaps[] = { srvHeap.Get() };
						commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);


						for (size_t p = srvParamOffset; p < srvParamOffset + srvParamCount; ++p) {
							commandList->SetGraphicsRootDescriptorTable(p, srvHeap->GetGPUDescriptorHandleForHeapStart());
						}

						//apply constant buffers
						for (size_t k = 0; k < compiled_params.buffers.size(); ++k) {
							commandList->SetGraphicsRootConstantBufferView(k, compiled_params.buffers[k].buffer->GetGPUVirtualAddress());
						}


						commandList->DrawIndexedInstanced(submesh->GetIndicesCount(), 1, 0, 0, 0);
					
					//renderer->EndCommandList();
					//renderer->WaitCommandsQueue();
				}
			}
		}
	}

	//commandList = renderer->BeginCommandList();
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(rt.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	renderer->EndCommandList();
	renderer->WaitCommandsQueue();

	

	renderScreen->Present();
	//signatures.clear();
	//renderer->reportLiveObjects();

	scene->GetGizmos().PrepareRender();
	scene->GetGizmos().DrawAll(camera);
	scene->GetGizmos().Clear();
}