#ifndef Submesh_h__
#define Submesh_h__

#include <vector>
#include "LEngine.h"
#include "d3d11_types.h"
#include <memory>
#include "d3dx12.h"

enum class MeshTopology {
	TriangleList,
	TriangleStrip,
	LineList,
	LineStrip
};

class Submesh {
public:
	typedef uint32_t index_count_t;
	typedef uint32_t index_t;
	typedef std::vector<index_t> index_array_t;

	Submesh() 
		:_indexCount(0)
	{

	}
	ID3D12ResourcePtr GetIndexBuffer() const{
		return _indexBuffer;
	}

	MeshTopology GetTopology() const{
		return _topology;
	}

	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView()
	{
		return _indexBufferView;
	}

	void Set(index_array_t indices, MeshTopology topology) {
		_indexCount = indices.size();
		_topology = topology;
		_indexBuffer = nullptr;

		if (_indexCount == 0) {
			return;
		}

		D3D11_BUFFER_DESC desc = { 0 };
		D3D11_SUBRESOURCE_DATA data = { 0 };

		//index buffer
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(indices[0]) * indices.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		data.pSysMem = &indices[0];
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		auto renderer = LEngine::Instance()->GetRenderer();
		auto device = renderer->GetDevice();
		auto cmdList = renderer->BeginCommandList();

		//create temporal upload resource
		ComPtr<ID3D12Resource> uploadBuffer;
		device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES,
			&CD3DX12_RESOURCE_DESC::Buffer(desc.ByteWidth),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadBuffer));


		//upload data to temporal resource
		void* p;
		uploadBuffer->Map(0, nullptr, &p);
		memcpy(p, &indices[0], desc.ByteWidth);
		uploadBuffer->Unmap(0, nullptr);

		device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(desc.ByteWidth),
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&_indexBuffer));


		_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
		_indexBufferView.SizeInBytes = desc.ByteWidth;
		_indexBufferView.Format = DXGI_FORMAT_R32_UINT;


		cmdList->CopyBufferRegion(_indexBuffer.Get(), 0, uploadBuffer.Get(), 0, desc.ByteWidth);

		CD3DX12_RESOURCE_BARRIER barriers[1] = {
			CD3DX12_RESOURCE_BARRIER::Transition(_indexBuffer.Get(),
			D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER)
		};


		cmdList->ResourceBarrier(1, barriers);
		renderer->EndCommandList();
		renderer->WaitCommandsQueue();
	}
	index_count_t GetIndicesCount() const {
		return _indexCount;
	}
private:
	index_count_t _indexCount;
	MeshTopology _topology;
	ID3D12ResourcePtr _indexBuffer;
	D3D12_INDEX_BUFFER_VIEW _indexBufferView;
};

typedef std::shared_ptr<Submesh> SubmeshPtr;
#endif // Submesh_h__
