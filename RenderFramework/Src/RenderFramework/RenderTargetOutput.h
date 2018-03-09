#ifndef RenderTargetOutput_h__
#define RenderTargetOutput_h__

#include "RenderOutput.h"
#include "d3d11_types.h"
#include "Renderer.h"


/*
class RenderTargetOutput : public RenderOutput {
public:
	static std::shared_ptr<RenderTargetOutput> Create(RendererPtr renderer);
	virtual uint32_t GetWidth() override;
	virtual uint32_t GetHeight() override;
	virtual ID3D11RenderTargetViewPtr GetRenderTargetView() override;
	virtual ID3D11DepthStencilViewPtr GetDepthStencilView() override;
	virtual void Present() override;
	virtual void OnPreRender(RendererPtr renderer) override;
	void Resize(uint32_t width, uint32_t height);
private:
	RenderTargetOutput(RendererPtr renderer);
	ID3D11DepthStencilViewPtr _dsView;
	ID3D11RenderTargetViewPtr _rtView;
	ID3D11Texture2DPtr _ds;
	ID3D11Texture2DPtr _rt;
	RendererPtr _renderer;
};*/
#endif // RenderTargetOutput_h__
