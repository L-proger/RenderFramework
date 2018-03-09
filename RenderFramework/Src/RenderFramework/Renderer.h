#ifndef Renderer_h__
#define Renderer_h__

#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_5.h>
#include <d3d11.h>
#include <d3d12.h>
#include <vector>
#include "FatalError.h"
#include <memory>
#include "d3d11_types.h"
#include <dxgidebug.h>
#include <sstream>
#include "D3d12DescriptorHeapAllocator.h"

#include <wrl.h>

using namespace Microsoft::WRL;

#define HR_ASSERT_MSG(__hr_expression, __message)\
while(true){\
	HRESULT hr_ = (__hr_expression);\
	if (FAILED(hr_)) {\
			std::wstringstream ss; \
			ss << L"Application fail with HRESULT:" << hr_ << " in file " << TEXT(__FILE__) << " at line " << __LINE__ << L" with message: " << __message; \
			FatalError(ss.str().c_str()); \
	}\
break;\
}


#define HR_ASSERT(__hr_expression) HR_ASSERT_MSG(__hr_expression, "")



class Renderer {
public:
	bool Init();
	
	ID3D12DevicePtr GetDevice();

	ComPtr<IDXGIAdapter1> GetAdapter() {
		return dxgiAdapter;
	}
	ComPtr<IDXGIFactory4> GetFactory() {
		return dxgiFactory;
	}

	ComPtr<ID3D12GraphicsCommandList> BeginCommandList();
	void EndCommandList();
	
	std::vector<IDXGIOutput1Ptr> EnumOutputs();
	IDXGISwapChain1Ptr CreateSwapChain(HWND window, bool windowed, uint32_t width, uint32_t height, uint32_t buffers_count, bool stereo);
	std::vector<DXGI_MODE_DESC1> GetDisplayModes(DXGI_FORMAT format, IDXGIOutput1Ptr output);
	std::vector<DXGI_MODE_DESC1> GetStereoModes(std::vector<DXGI_MODE_DESC1>& modes);
	void WaitCommandsQueue();

	std::shared_ptr<D3d12DescriptorHeapAllocator> getSrvDescriptorsAllocator();

	void reportLiveObjects() const;
private:
	ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
	ID3D12DevicePtr device;
	IDXGIAdapter1Ptr dxgiAdapter;
	IDXGIFactory4Ptr dxgiFactory;

	ComPtr<ID3D12CommandQueue> _directCommandQueue;
	ComPtr<ID3D12GraphicsCommandList> _directCommandList;
	ComPtr<ID3D12CommandAllocator> _directCommandAllocator;

	ComPtr<ID3D12DescriptorHeap> _srvDescriptorsHeap;
	std::shared_ptr<D3d12DescriptorHeapAllocator> _srvDescriptorAllocator;
};

typedef std::shared_ptr<Renderer> RendererPtr;


#endif // Renderer_h__
