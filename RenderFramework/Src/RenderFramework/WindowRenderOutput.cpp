#include "WindowRenderOutput.h"
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include "LEngine.h"
/*
std::vector<DXGI_MODE_DESC1> GetDisplayModes(DXGI_FORMAT format, CComPtr<IDXGIOutput1> output) {
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

std::vector<DXGI_MODE_DESC1> GetStereoModes(std::vector<DXGI_MODE_DESC1>& modes) {
	std::vector<DXGI_MODE_DESC1> result;
	for (auto& m : modes) {
		if (m.Stereo) {
			result.push_back(m);
		}
	}
	return result;
}

std::vector<DXGI_MODE_DESC1> GetModesByResolution(std::vector<DXGI_MODE_DESC1>& modes, UINT width, UINT height) {
	std::vector<DXGI_MODE_DESC1> result;
	for (auto& m : modes) {
		if (m.Width == width && m.Height == height) {
			result.push_back(m);
		}
	}
	return result;
}

bool FindModeByRefreshRate(UINT targetRate, std::vector<DXGI_MODE_DESC1>& modes, DXGI_MODE_DESC1& mode) {
	for (auto& m : modes) {
		auto refreshRate = m.RefreshRate.Numerator / m.RefreshRate.Denominator;
		int range = 2;
		//test if in range
		if ((refreshRate >= (targetRate - range)) && (refreshRate <= (targetRate + range))) {
			mode = m;
			return true;
		}
	}
	return false;
}


WindowRenderOutput::WindowRenderOutput(){

}

WindowRenderOutput::~WindowRenderOutput()
{
}

Window& WindowRenderOutput::GetWindow() {
	return _window;
}

void WindowRenderOutput::Init(){
	_window.Init();*/
	/*NettleDisplayManager::EDID edid;
	NettleDisplayManager::ReadEdidForDxgiOutput(vOutputs[0], edid);
	auto& mainEdidBlock = edid.GetMainBlock();

	auto hSize = mainEdidBlock.detailedTimingDescriptions.detailedTimingDescription1.horizontalBlanking.GetActivePixels();
	auto vSize = mainEdidBlock.detailedTimingDescriptions.detailedTimingDescription1.verticalBlanking.GetActivePixels();*/
	/*
	auto hSize = 640;
	auto vSize = 480;

	auto backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;

	CComPtr<IDXGIOutput> pOutput;
	std::vector<CComPtr<IDXGIOutput>> vOutputs;
	int outputId = 0;
	while (LEngine::Instance()->GetRenderer()->GetAdapter()->EnumOutputs(outputId, &pOutput) != DXGI_ERROR_NOT_FOUND) {
		vOutputs.push_back(pOutput);
		pOutput = nullptr;
		++outputId;
	}

	DXGI_OUTPUT_DESC desc;
	vOutputs[0]->GetDesc(&desc);
	_output = vOutputs[0];

	CComPtr<IDXGIOutput1> testOutput;
	vOutputs[0].QueryInterface(&testOutput);
	auto displayModes = GetDisplayModes(backBufferFormat, testOutput);
	//auto stereoModes = GetModesByResolution(GetStereoModes(displayModes), 1920, 1080);
	auto stereoModes = GetModesByResolution(displayModes, hSize, vSize);

	DXGI_MODE_DESC1 targetMode = { 0 };
	if (!FindModeByRefreshRate(60, stereoModes, targetMode)) {
		FatalError(TEXT("Failed to find 1920 x 1080 stereo 60Hz mode!"));
	}

	// Allocate a descriptor.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = targetMode.Width;
	swapChainDesc.Height = targetMode.Height;
	swapChainDesc.Format = targetMode.Format;
	swapChainDesc.Stereo = targetMode.Stereo;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC  fullscreenDesc = { 0 };
	fullscreenDesc.RefreshRate = targetMode.RefreshRate;
	fullscreenDesc.ScanlineOrdering = targetMode.ScanlineOrdering;
	fullscreenDesc.Scaling = targetMode.Scaling;
	fullscreenDesc.Windowed = TRUE;

	//create swap chain
	if (S_OK != LEngine::Instance()->GetRenderer()->GetFactory()->CreateSwapChainForHwnd(LEngine::Instance()->GetRenderer()->GetDevice(), _window.GetHwnd(), &swapChainDesc, &fullscreenDesc, nullptr, &_swapChain)) {
		FatalError(TEXT("Failed to create swap chain"));
	}

	//get back buffer

	_swapChain->GetBuffer(0, IID_PPV_ARGS(&_backBuffer));

	//left eye

	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDescLeft(D3D11_RTV_DIMENSION_TEXTURE2DARRAY, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, 1);
	if (S_OK != LEngine::Instance()->GetRenderer()->GetDevice()->CreateRenderTargetView(_backBuffer, &renderTargetViewDescLeft, &_leftRtv)) {
		FatalError(TEXT("Failed to create left eye RTV"));
	}

	bool forceStereo = false;


	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = swapChainDesc.Width;
	descDepth.Height = swapChainDesc.Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	auto hr = LEngine::Instance()->GetRenderer()->GetDevice()->CreateTexture2D(&descDepth, NULL, &_depthBuffer);

	LEngine::Instance()->GetRenderer()->GetDevice()->CreateDepthStencilView(_depthBuffer, nullptr, &_depthStencilView);
	*/
	//right eye
	/*CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDescRight(D3D11_RTV_DIMENSION_TEXTURE2DARRAY, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 1, 1);
	if(S_OK != device->CreateRenderTargetView(backBuffer, &renderTargetViewDescRight, &rightRtv)) {
	if(forceStereo) {
	FatalError(TEXT("Failed to create right eye RTV"));
	} else {
	rightRtv = nullptr;
	}

	}*//*
}

ID3D11DepthStencilViewPtr WindowRenderOutput::GetDepthStencilView() {
	return _depthStencilView;
}

void WindowRenderOutput::Update() {
	_window.ProcessMessages();
}

void WindowRenderOutput::OnPreRender(RendererPtr renderer){
	uint32_t w, h;
	_window.GetWindowSize(w, h);
	D3D11_TEXTURE2D_DESC desc;
	_backBuffer->GetDesc(&desc);

	if (desc.Width != w || desc.Height != h) {
		_backBuffer = nullptr;
		_leftRtv = nullptr;
		_rightRtv = nullptr;
		auto hr = _swapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
		if (hr != S_OK) {
			assert(false && "Can't resize BB");
		}

		_swapChain->GetBuffer(0, IID_PPV_ARGS(&_backBuffer));

		//left eye
		CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDescLeft(D3D11_RTV_DIMENSION_TEXTURE2DARRAY, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0, 1);
		if (S_OK != renderer->GetDevice()->CreateRenderTargetView(_backBuffer, &renderTargetViewDescLeft, &_leftRtv)) {
			FatalError(TEXT("Failed to create left eye RTV"));
		}
	}

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)w;
	viewport.Height = (float)h;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	renderer->GetImmediateContext()->RSSetViewports(1, &viewport);
}

void WindowRenderOutput::Present() {
	DXGI_PRESENT_PARAMETERS parameters = { 0 };
	parameters.DirtyRectsCount = 0;
	parameters.pDirtyRects = nullptr;
	parameters.pScrollRect = nullptr;
	parameters.pScrollOffset = nullptr;
	HRESULT hr = _swapChain->Present1(0, 0, &parameters);
}

uint32_t WindowRenderOutput::GetWidth(){
	D3D11_TEXTURE2D_DESC desc;
	_backBuffer->GetDesc(&desc);
	return desc.Width;
}

uint32_t WindowRenderOutput::GetHeight(){
	D3D11_TEXTURE2D_DESC desc;
	_backBuffer->GetDesc(&desc);
	return desc.Height;
}

CComPtr<ID3D11RenderTargetView> WindowRenderOutput::GetRenderTargetView(){
	return _leftRtv;
}
*/