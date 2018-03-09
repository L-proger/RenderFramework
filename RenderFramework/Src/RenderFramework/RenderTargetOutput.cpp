#include "RenderTargetOutput.h"
/*
std::shared_ptr<RenderTargetOutput> RenderTargetOutput::Create(RendererPtr renderer) {
	return std::shared_ptr<RenderTargetOutput>(new RenderTargetOutput(renderer));
}
RenderTargetOutput::RenderTargetOutput(RendererPtr renderer) 
	:_renderer(renderer) {

}
uint32_t RenderTargetOutput::GetWidth() {
	if (_rt == nullptr) {
		return 0;
	}
	D3D11_TEXTURE2D_DESC desc;
	_rt->GetDesc(&desc);
	return desc.Width;
}
uint32_t RenderTargetOutput::GetHeight() {
	if (_rt == nullptr) {
		return 0;
	}
	D3D11_TEXTURE2D_DESC desc;
	_rt->GetDesc(&desc);
	return desc.Height;
}
ID3D11RenderTargetViewPtr RenderTargetOutput::GetRenderTargetView() {
	return _rtView;
}
ID3D11DepthStencilViewPtr RenderTargetOutput::GetDepthStencilView() {
	return _dsView;
}
void RenderTargetOutput::Present() {

}
void RenderTargetOutput::OnPreRender(RendererPtr renderer) {

}
void RenderTargetOutput::Resize(uint32_t width, uint32_t height) {
	if (_rt != nullptr) {
		D3D11_TEXTURE2D_DESC desc;
		_rt->GetDesc(&desc);
		if (desc.Width == width && desc.Height == height) {
			return;
		}
	}

	_rt = nullptr;
	_ds = nullptr;
	_rtView = nullptr;
	_dsView = nullptr;

	D3D11_TEXTURE2D_DESC desc = { 0 };
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	auto hr = _renderer->GetDevice()->CreateTexture2D(&desc, nullptr, &_rt);
	hr = _renderer->GetDevice()->CreateRenderTargetView(_rt, nullptr, &_rtView);

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = _renderer->GetDevice()->CreateTexture2D(&descDepth, NULL, &_ds);
	hr = _renderer->GetDevice()->CreateDepthStencilView(_ds, nullptr, &_dsView);
}*/