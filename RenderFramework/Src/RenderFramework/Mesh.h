#ifndef Mesh_h__
#define Mesh_h__

#include <vector>
#include <stdint.h>
#include <memory>
#include <functional>
#include "ForwardDeclarations.h"
#include "Vertex.h"
#include "Submesh.h"
#include "Bounds.h"
#include "Object.h"

#include <wrl.h>

using namespace Microsoft::WRL;

typedef std::function<void(MeshPtr)> MeshProcessFunction;

class Mesh : public Object {
public:
	Mesh():_vertexCount(0)
	{
		
	}
	std::vector<Vertex> GetVertices();
	void SetVertices(const std::vector<Vertex>& vertices);
	void SetIndices(const Submesh::index_array_t& indices, MeshTopology topology, uint32_t submeshId);
	void RecalculateBounds();
	ID3D12ResourcePtr GetVertexBuffer();
	ID3D12DevicePtr GetDevice();
	static MeshPtr Create();
	static MeshPtr Create(MeshProcessFunction initFunction);
	uint32_t GetSubmeshCount() const;
	void SetSubmeshCount(uint32_t count);
	const std::vector<SubmeshPtr>& GetSubmeshes();
	Bounds GetBounds() const;
	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
private:
	size_t _vertexCount;
	Bounds _bounds;
	Mesh(ID3D12DevicePtr dev);
	ID3D12ResourcePtr _vertexBuffer;
	ID3D12DevicePtr _device;
	std::vector<SubmeshPtr> _submeshes;
};


#endif // Mesh_h__
