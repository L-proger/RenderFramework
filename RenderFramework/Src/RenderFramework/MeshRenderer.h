#ifndef MeshRenderer_h__
#define MeshRenderer_h__

#include "ObjectsFactory.h"
#include "Mesh.h"
#include "Material.h"
#include <vector>
#include "ForwardDeclarations.h"
#include <memory>


LOBJECT(MeshRenderer, Component)
public:
	std::shared_ptr<MeshRenderer> SetMesh(MeshPtr m);
	MeshPtr GetMesh();
	void SetMaterial(MaterialPtr material, int id);
	std::vector<MaterialPtr> GetMaterials() {
		return _materials;
	}
	D3D12_INPUT_LAYOUT_DESC GetInputLayout() {
		return _inputLayoutDesc;
	}
private:
	void UpdateInputLayouts();
	void SyncMaterialSlots();
	MeshPtr mesh;
	std::vector<MaterialPtr> _materials;
	std::vector<D3D12_INPUT_ELEMENT_DESC> _inputElements;
	D3D12_INPUT_LAYOUT_DESC _inputLayoutDesc;
};
#endif // MeshRenderer_h__
