#ifndef WindowScreen_h__
#define WindowScreen_h__
/*
#include "RenderOutput.h"
#include "Renderer.h"
#include "d3d11_types.h"

class WindowRenderOutput : public RenderOutput
{
public:
	WindowRenderOutput();
	~WindowRenderOutput();
	void Init();
	void OnPreRender(RendererPtr renderer) override;
	void Present() override;
	void Update();
	virtual uint32_t GetWidth() override;
	virtual uint32_t GetHeight() override;
	virtual ID3D11RenderTargetViewPtr GetRenderTargetView() override;
	virtual ID3D11DepthStencilViewPtr GetDepthStencilView() override;
	Window& GetWindow();
private:
	Window _window;
	IDXGIOutputPtr _output;
	ID3D11Texture2DPtr _backBuffer;
	ID3D11Texture2DPtr _depthBuffer;
	ID3D11RenderTargetViewPtr _leftRtv;
	ID3D11RenderTargetViewPtr _rightRtv;
	ID3D11DepthStencilViewPtr _depthStencilView;
	IDXGISwapChain1Ptr _swapChain;
};*/
#endif // WindowScreen_h__
