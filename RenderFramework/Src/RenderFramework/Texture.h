#ifndef Texture_h__
#define Texture_h__

#include <d3d12.h>
#include "d3d11_types.h"

class Texture
{
public:
	Texture(ID3D12ResourcePtr _resource, D3D12_CPU_DESCRIPTOR_HANDLE _srvDescriptor)
		:resource(_resource), srvDescriptor(_srvDescriptor)
	{
		
	}
	ID3D12ResourcePtr resource;
	D3D12_CPU_DESCRIPTOR_HANDLE srvDescriptor;
};
#endif // Texture_h__
