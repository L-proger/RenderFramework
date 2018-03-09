#include "AssetManager.h"
#include "DirectXTex/DirectXTex.h"
#include "DDSTextureLoader12.h"
#include "LEngine.h"
#include "Texture.h"

std::shared_ptr<AssetManager> AssetManager::_instance = nullptr;

TexturePtr AssetManager::LoadTexture(const std::wstring& path) const
{
	auto renderer = LEngine::Instance()->GetRenderer();
	auto device = renderer->GetDevice();

	ID3D12ResourcePtr resource;

	std::unique_ptr<uint8_t[]> data;
	std::vector<D3D12_SUBRESOURCE_DATA> srData;
	DirectX::LoadDDSTextureFromFile(device.Get(), GetFullAssetPath(path).c_str(), &resource, data, srData);

	//auto cmdList = renderer->BeginCommandList();


	//create upload heap
	D3D12_RESOURCE_DESC desc;
	desc = resource->GetDesc();

	UINT64 textureUploadBufferSize;
	device->GetCopyableFootprints(&desc, 0, srData.size(), 0, nullptr, nullptr, nullptr, &textureUploadBufferSize);

	// now we create an upload heap to upload our texture to the GPU
	ID3D12ResourcePtr textureBufferUploadHeap;
	auto hr = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // upload heap
		D3D12_HEAP_FLAG_NONE, // no flags
		&CD3DX12_RESOURCE_DESC::Buffer(textureUploadBufferSize), // resource description for a buffer (storing the image data in this heap just to copy to the default heap)
		D3D12_RESOURCE_STATE_GENERIC_READ, // We will copy the contents from this heap to the default heap above
		nullptr,
		IID_PPV_ARGS(&textureBufferUploadHeap));
	if (FAILED(hr))
	{
		FatalError(L"Failed to create upload heap");
	}
	textureBufferUploadHeap->SetName(L"Texture Buffer Upload Resource Heap");

	auto commandList = renderer->BeginCommandList();
	//copy subresource
	UpdateSubresources(commandList.Get(), resource.Get(), textureBufferUploadHeap.Get(), 0, 0, srData.size(), &srData[0]);
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));


	renderer->EndCommandList();
	renderer->WaitCommandsQueue();

	//create shader resource view
	auto srvMemory = renderer->getSrvDescriptorsAllocator()->alloc();

	D3D12_RESOURCE_DESC texDesc;
	texDesc = resource->GetDesc();


	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	device->CreateShaderResourceView(resource.Get(), &srvDesc, srvMemory);


	auto result = std::make_shared<Texture>(resource, srvMemory);
	
	//DirectX::CreateTexture(renderer->GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &resource);
	return result;
}
