#include "Renderer.h"
#include <iostream>
#include "d3dx12.h"
#include <dxgidebug.h>

bool Renderer::Init() {
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}

	//Enable DXGI debug layer
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiInfoQueue)))) {
		dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
		dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
		dxgiInfoQueue->SetMuteDebugOutput(DXGI_DEBUG_ALL, FALSE);
	}
	
	

	auto hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgiFactory));
	dxgiFactory->EnumAdapters1(0, &dxgiAdapter);

	IDXGIAdapter1Ptr warpAdapter;
	//dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));
	warpAdapter = dxgiAdapter;

	DXGI_ADAPTER_DESC desc;
	warpAdapter->GetDesc(&desc);
	std::wcout << "Using adapter: " << desc.Description << std::endl;

	HR_ASSERT(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)));

	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_directCommandQueue));
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_directCommandAllocator));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _directCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&_directCommandList));


	//create descriptor heaps
	
	constexpr size_t descriptorHeapsSize = 512;

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = descriptorHeapsSize;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	hr = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&_srvDescriptorsHeap));
	if (FAILED(hr))
	{
		FatalError(L"Failed to create SRV descriptors heap");
	}
	_srvDescriptorsHeap->SetName(L"SRV Heap");

	_srvDescriptorAllocator = std::make_shared<D3d12DescriptorHeapAllocator>(_srvDescriptorsHeap);

	return true;
}

void Renderer::reportLiveObjects() const
{
	IDXGIDebug1* pDebug = nullptr;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug)))) {
		pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		pDebug->Release();
	}
}

std::shared_ptr<D3d12DescriptorHeapAllocator> Renderer::getSrvDescriptorsAllocator(){
	return _srvDescriptorAllocator;
}

ComPtr<ID3D12GraphicsCommandList> Renderer::BeginCommandList(){
	auto HR = _directCommandAllocator->Reset();
	HR = _directCommandList->Reset(_directCommandAllocator.Get(), nullptr);
	return _directCommandList;
}

void Renderer::EndCommandList(){
	_directCommandList->Close();
	ID3D12CommandList* ppCommandLists[] = { _directCommandList.Get()};
	_directCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

void Renderer::WaitCommandsQueue(){
	ID3D12Fence* fence = nullptr;
	HRESULT hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (hr)
		return;

	auto eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);

	_directCommandQueue->Signal(fence, 1);
	fence->SetEventOnCompletion(1, eventHandle);
	WaitForSingleObject(eventHandle, INFINITE);

	CloseHandle(eventHandle);
	fence->Release();
}

ID3D12DevicePtr Renderer::GetDevice() {
	return device;
}

std::vector<IDXGIOutput1Ptr> Renderer::EnumOutputs() {
	IDXGIOutput1Ptr pOutput;
	std::vector<IDXGIOutput1Ptr> vOutputs;
	int outputId = 0;

	IDXGIOutputPtr o;
	while (GetAdapter()->EnumOutputs(outputId, &o) != DXGI_ERROR_NOT_FOUND) {
		o->QueryInterface(IID_PPV_ARGS(&pOutput));
		vOutputs.push_back(pOutput);
		pOutput = nullptr;
		o = nullptr;
		++outputId;
	}
	return vOutputs;
}

IDXGISwapChain1Ptr Renderer::CreateSwapChain(HWND window, bool windowed, uint32_t width, uint32_t height, uint32_t buffers_count, bool stereo) {
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = stereo;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = buffers_count;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.Flags = 0;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

	/*DXGI_SWAP_CHAIN_FULLSCREEN_DESC  fullscreenDesc = { 0 };
	fullscreenDesc.RefreshRate = {60 ,0};
	fullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	fullscreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	fullscreenDesc.Windowed = windowed;*/

	IDXGISwapChain1Ptr result;
	auto hr = GetFactory()->CreateSwapChainForHwnd(_directCommandQueue.Get(), window, &swapChainDesc, nullptr, nullptr, &result);
	if (S_OK != hr){
		FatalError(TEXT("Failed to create swap chain"));
	}
	return result;
}

//auto backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;

std::vector<DXGI_MODE_DESC1> Renderer::GetDisplayModes(DXGI_FORMAT format, IDXGIOutput1Ptr output) {
	std::vector<DXGI_MODE_DESC1> result;
	UINT numStereoModes = 0;
	DXGI_MODE_DESC1 modes[1024];
	auto enumFlags = DXGI_ENUM_MODES_STEREO;

	output->GetDisplayModeList1(format, enumFlags, &numStereoModes, 0);
	output->GetDisplayModeList1(format, enumFlags, &numStereoModes, modes);

	for (UINT i = 0; i < numStereoModes; ++i) {
		result.push_back(modes[i]);
	}
	return result;
}

std::vector<DXGI_MODE_DESC1> Renderer::GetStereoModes(std::vector<DXGI_MODE_DESC1>& modes) {
	std::vector<DXGI_MODE_DESC1> result;
	for (auto& m : modes) {
		if (m.Stereo) {
			result.push_back(m);
		}
	}
	return result;
}