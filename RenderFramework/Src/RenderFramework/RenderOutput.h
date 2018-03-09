#ifndef Screen_h__
#define Screen_h__

#include <d3d11.h>
#include <cassert>
#include <stdint.h>
#include "Renderer.h"
#include "d3d11_types.h"
#include <memory>
#include "d3dx12.h"
#include <vector>
#include <wrl.h>

using namespace Microsoft::WRL;

class RenderOutput {
public:

	virtual ~RenderOutput() {
	}
	virtual uint32_t GetWidth() = 0;
	virtual uint32_t GetHeight() = 0;

	virtual CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetDescriptor(uint32_t id) = 0;
	virtual CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilDescriptor(uint32_t id) = 0;

	virtual ID3D12ResourcePtr GetRenderTarget(uint32_t id) = 0;
	virtual ID3D12ResourcePtr GetDepthBuffer(uint32_t id) = 0;

	virtual void Present() = 0;
	virtual void OnPreRender(RendererPtr renderer) = 0;

	virtual uint32_t GetCurrentBufferIndex() = 0;
	virtual uint32_t GetBuffersCount() = 0;
protected:
};

typedef std::shared_ptr<RenderOutput> RenderOutputPtr;
#endif // Screen_h__
