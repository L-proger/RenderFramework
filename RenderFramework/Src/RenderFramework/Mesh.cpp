#include "Mesh.h"
#include "LEngine.h"
#include <string.h>

Mesh::Mesh(ID3D12DevicePtr dev) {
	_device = dev;
	SetSubmeshCount(1);
}

MeshPtr Mesh::Create() {
	return std::shared_ptr<Mesh>(new Mesh(LEngine::Instance()->GetRenderer()->GetDevice()));
}

ID3D12ResourcePtr Mesh::GetVertexBuffer() {
	return _vertexBuffer;
}

ID3D12DevicePtr Mesh::GetDevice() {
	return _device;
}

MeshPtr Mesh::Create(MeshProcessFunction initFunction) {
	auto mesh = Create();
	if (initFunction != nullptr) {
		initFunction(mesh);
		mesh->RecalculateBounds();
	}
	return mesh;
}

Bounds Mesh::GetBounds() const {
	return _bounds;
}

std::vector<Vertex> Mesh::GetVertices() {
	std::vector<Vertex> result;
	/*if (_vertexBuffer == nullptr) {
		return result;
	}

	D3D11_BUFFER_DESC desc;
	_vertexBuffer->GetDesc(&desc);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	ID3D11BufferPtr stagingBuffer;
	_device->CreateBuffer(&desc, nullptr, &stagingBuffer);
	ID3D11DeviceContextPtr ctx;
	_device->GetImmediateContext(&ctx);

	ctx->CopyResource(stagingBuffer, _vertexBuffer);
	D3D11_MAPPED_SUBRESOURCE sr;
	ctx->Map(stagingBuffer, 0, D3D11_MAP_READ, 0, &sr);
	result.resize(desc.ByteWidth / sizeof(Vertex));
	memcpy_s(&result[0], desc.ByteWidth, sr.pData, desc.ByteWidth);
	ctx->Unmap(stagingBuffer, 0);*/
	return result;
}

D3D12_VERTEX_BUFFER_VIEW Mesh::GetVertexBufferView(){
	D3D12_VERTEX_BUFFER_VIEW result;
	result.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	result.SizeInBytes = _vertexCount * sizeof(Vertex);
	result.StrideInBytes = sizeof(Vertex);
	return result;
}

void Mesh::SetVertices(const std::vector<Vertex>& vertices) {
	auto bytesCount = sizeof(vertices[0])* vertices.size();
	_vertexCount = vertices.size();


	//create vertex buffer
	_device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bytesCount), 
		D3D12_RESOURCE_STATE_COPY_DEST, 					
		nullptr, 
		IID_PPV_ARGS(&_vertexBuffer));


	//create upload buffer
	ComPtr<ID3D12Resource> vBufferUploadHeap;
	_device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bytesCount),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vBufferUploadHeap));
	vBufferUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");


	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData = reinterpret_cast<const BYTE*>(&vertices[0]); // pointer to our vertex array
	vertexData.RowPitch = bytesCount; // size of all our triangle vertex data
	vertexData.SlicePitch = bytesCount; // also the size of our triangle vertex data


	auto renderer = LEngine::Instance()->GetRenderer();
	auto cl = renderer->BeginCommandList();
	UpdateSubresources(cl.Get(), _vertexBuffer.Get(), vBufferUploadHeap.Get(), 0, 0, 1, &vertexData);
	cl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));
	renderer->EndCommandList();
	renderer->WaitCommandsQueue();
}

void Mesh::SetIndices(const Submesh::index_array_t& indices, MeshTopology topology, uint32_t submeshId) {
	if (submeshId >= GetSubmeshCount()) {
		return;
	}
	_submeshes[submeshId]->Set(indices, topology);
}

uint32_t Mesh::GetSubmeshCount() const {
	return _submeshes.size();
}
void Mesh::SetSubmeshCount(uint32_t count) {
	auto oldSize = _submeshes.size();
	_submeshes.resize(count);
	for (auto i = oldSize; i < count; ++i) {
		_submeshes[i] = std::make_shared<Submesh>();
	}
}

const std::vector<SubmeshPtr>& Mesh::GetSubmeshes() {
	return _submeshes;
}

void Mesh::RecalculateBounds() {
	/*auto vertices = GetVertices();
	if (vertices.size() == 0) {
		_bounds.SetSize(float3(0, 0, 0));
		_bounds.SetCenter(float3(0, 0, 0));
	}

	float3 minPoint = vertices[0].position.xyz;
	float3 maxPoint = vertices[0].position.xyz;

	for (size_t i = 1; i < vertices.size(); ++i) {
		minPoint = lm::min(minPoint, vertices[i].position.xyz);
		maxPoint = lm::max(maxPoint, vertices[i].position.xyz);
	}

	_bounds.SetCenter((minPoint + maxPoint) * 0.5f);
	_bounds.SetSize(maxPoint - minPoint);*/
}