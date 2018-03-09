#include "MeshRenderer.h"
#include <cassert>

void MeshRenderer::SyncMaterialSlots() {
	if (mesh == nullptr) {
		_materials.resize(0);
	}
	else {
		_materials.resize(mesh->GetSubmeshCount());
	}
}

std::shared_ptr<MeshRenderer> MeshRenderer::SetMesh(MeshPtr m) {
	mesh = m;
	SyncMaterialSlots();
	UpdateInputLayouts();
	return std::static_pointer_cast<MeshRenderer>(shared_from_this());
}

MeshPtr MeshRenderer::GetMesh() {
	return mesh;
}

void MeshRenderer::SetMaterial(MaterialPtr material, int id){
	SyncMaterialSlots();
	_materials[id] = material;
	UpdateInputLayouts();
}

void MeshRenderer::UpdateInputLayouts(){

	if (mesh == nullptr) {
		return;
	}

	if (_materials.size() == 0 || _materials[0] == nullptr) {
		return;
	}

	//D3D12_APPEND_ALIGNED_ELEMENT
	_inputElements.clear();
	_inputElements.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,  0,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
	_inputElements.push_back({ "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
	_inputElements.push_back({ "UV",		0, DXGI_FORMAT_R32G32_FLOAT,		0,  28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
	_inputElements.push_back({ "UV",		1, DXGI_FORMAT_R32G32_FLOAT,		0,  36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });

	
	_inputLayoutDesc.NumElements = _inputElements.size();
	_inputLayoutDesc.pInputElementDescs = &_inputElements[0];

	//auto vs = _materials[0]->GetShader()->GetShader(ShaderType::Vs);
	//auto hr = mesh->GetDevice()->CreateInputLayout(ied, 4, vs->blob->GetBufferPointer(), vs->blob->GetBufferSize(), &_inputLayout);
	//assert(hr == S_OK);
}
