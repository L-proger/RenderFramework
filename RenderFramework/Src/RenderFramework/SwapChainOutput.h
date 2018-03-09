#pragma once

#include "RenderOutput.h"
#include "d3d11_types.h"
#include "Renderer.h"
#include "d3dx12.h"


class SwapChainOutput : public RenderOutput {
public:
	SwapChainOutput(RendererPtr renderer, HWND window, uint32_t width, uint32_t height, bool stereo) : _activeBuffer(0){
		_buffersCount = 2;
		_swapChain = renderer->CreateSwapChain(window, true, width, height, _buffersCount, stereo);
		auto device = renderer->GetDevice();

		//create RTV descriptors heap
		D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
		heap_desc.NumDescriptors = _buffersCount; 
		heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; 
		heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		HR_ASSERT_MSG(device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&rtvDescriptorHeap)), L"Failed to allocate RTV descriptors heap");
		rtvDescriptorHeap->SetName(L"RTV Heap");

		rtvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());


		//create DSV descriptors heap
		heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		HR_ASSERT_MSG(device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&dsvDescriptorHeap)), L"Failed to allocate DSV descriptors heap");
		dsvDescriptorHeap->SetName(L"DSV Heap");

		dsvDescSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

		for(uint32_t i = 0; i < _buffersCount; ++i){
			//get back buffer
			ID3D12ResourcePtr _backBuffer;
			if (FAILED(_swapChain->GetBuffer(i, IID_PPV_ARGS(&_backBuffer)))){
				FatalError(TEXT("Failed to get swap chain's bffer"));
			}
			device->CreateRenderTargetView(_backBuffer.Get(), nullptr, rtvHandle);
			


			//create depth buffer
			D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
			depthOptimizedClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
			depthOptimizedClearValue.DepthStencil.Stencil = 0;

			ComPtr<ID3D12Resource> depthStencilBuffer;
			device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D24_UNORM_S8_UINT, width, height, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
				D3D12_RESOURCE_STATE_DEPTH_WRITE,
				&depthOptimizedClearValue,
				IID_PPV_ARGS(&depthStencilBuffer)
			);

			device->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, dsvHandle);

			rtvHandle.Offset(1, rtvDescSize);
			dsvHandle.Offset(1, dsvDescSize);
			_buffers.push_back({ _backBuffer, depthStencilBuffer });
		}	
	}
	virtual uint32_t GetWidth() override{
		return GetDesc().Width;
	}

	virtual uint32_t GetHeight() override
	{
		return GetDesc().Height;
	}
	
	CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetDescriptor(uint32_t id) override {
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), id, rtvDescSize);
	}
	CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilDescriptor(uint32_t id) override {
		return CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), id, dsvDescSize);
	}

	ID3D12ResourcePtr GetRenderTarget(uint32_t id) override{
		return _buffers[id].first;
	}

	ID3D12ResourcePtr GetDepthBuffer(uint32_t id) override {
		return _buffers[id].second;
	}

	virtual void Present() override{
		_swapChain->Present(0, 0);
		_activeBuffer = (_activeBuffer + 1) % _buffersCount;
	}

	virtual void OnPreRender(RendererPtr renderer) override{
		
	}

	DXGI_SWAP_CHAIN_DESC1 GetDesc() {
		DXGI_SWAP_CHAIN_DESC1 desc;
		_swapChain->GetDesc1(&desc);
		return desc;
	}
	uint32_t GetCurrentBufferIndex() override{
		return _activeBuffer;
	}
	uint32_t GetBuffersCount() override{
		return _buffersCount;
	}
private:
	std::vector<std::pair<ID3D12ResourcePtr, ID3D12ResourcePtr>> _buffers;
	uint32_t _activeBuffer;
	uint32_t _buffersCount;
	UINT rtvDescSize;
	UINT dsvDescSize;
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;
	IDXGISwapChain1Ptr _swapChain;
	
};
