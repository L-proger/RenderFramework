#ifndef d3d11_types_h__
#define d3d11_types_h__

#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3d12.h>
#include <dxgi1_4.h>

#include <wrl.h>

using namespace Microsoft::WRL;

typedef ComPtr<ID3D11Buffer> ID3D11BufferPtr;
typedef ComPtr<ID3D11Device> ID3D11DevicePtr;
typedef ComPtr<ID3D11InputLayout> ID3D11InputLayoutPtr;
typedef ComPtr<ID3D11DepthStencilState> ID3D11DepthStencilStatePtr;

typedef ComPtr<ID3D11DeviceContext> ID3D11DeviceContextPtr;

typedef ComPtr<ID3D11ShaderResourceView> ID3D11ShaderResourceViewPtr;

typedef ComPtr<IDXGIOutput> IDXGIOutputPtr;
typedef ComPtr<ID3D11Texture2D> ID3D11Texture2DPtr;
typedef ComPtr<ID3D11Resource> ID3D11ResourcePtr;
typedef ComPtr<ID3D12Resource> ID3D12ResourcePtr;

typedef ComPtr<ID3D11RenderTargetView> ID3D11RenderTargetViewPtr;
typedef ComPtr<IDXGISwapChain1> IDXGISwapChain1Ptr;
typedef ComPtr<IDXGISwapChain> IDXGISwapChainPtr;
typedef ComPtr<ID3D11DepthStencilView> ID3D11DepthStencilViewPtr;

typedef ComPtr<IDXGIOutput1> IDXGIOutput1Ptr;


typedef ComPtr<IDXGIDevice1> IDXGIDevice1Ptr;
typedef ComPtr<IDXGIAdapter> IDXGIAdapterPtr;
typedef ComPtr<IDXGIAdapter1> IDXGIAdapter1Ptr;
typedef ComPtr<IDXGIFactory2> IDXGIFactory2Ptr;
typedef ComPtr<IDXGIFactory4> IDXGIFactory4Ptr;


typedef ComPtr<ID3D12Device> ID3D12DevicePtr;

#endif // d3d11_types_h__
