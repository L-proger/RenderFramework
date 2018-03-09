#include "Gizmos.h"
#include "GameObject.h"
#include "LEngine.h"
#include "d3d11_helper.h"
#include "LEngine.h"

Gizmos::Gizmos()
	:_color(0.0f, 1.0f, 0.0f, 1.0f)
{
	_matrix = float4x4::identity();
}
void Gizmos::SetMatrix(const float4x4& matrix) {
	_matrix = matrix;
}
float4x4 Gizmos::GetMatrix() {
	return _matrix;
}
void Gizmos::DrawBounds(const Bounds& bounds) {
	auto b = bounds;
	b.Scale(1.01f);
	auto bMin = b.Minimum();
	auto bMax = b.Maximum();

	DrawLine(float3(bMin.x(), bMax.y(), bMax.z()), float3(bMax.x(), bMax.y(), bMax.z()));
	DrawLine(float3(bMin.x(), bMax.y(), bMin.z()), float3(bMax.x(), bMax.y(), bMin.z()));
	DrawLine(float3(bMin.x(), bMax.y(), bMax.z()), float3(bMin.x(), bMax.y(), bMin.z()));
	DrawLine(float3(bMax.x(), bMax.y(), bMax.z()), float3(bMax.x(), bMax.y(), bMin.z()));

	DrawLine(float3(bMin.x(), bMin.y(), bMax.z()), float3(bMax.x(), bMin.y(), bMax.z()));
	DrawLine(float3(bMin.x(), bMin.y(), bMin.z()), float3(bMax.x(), bMin.y(), bMin.z()));
	DrawLine(float3(bMin.x(), bMin.y(), bMax.z()), float3(bMin.x(), bMin.y(), bMin.z()));
	DrawLine(float3(bMax.x(), bMin.y(), bMax.z()), float3(bMax.x(), bMin.y(), bMin.z()));
															
	DrawLine(float3(bMin.x(), bMin.y(), bMin.z()), float3(bMin.x(), bMax.y(), bMin.z()));
	DrawLine(float3(bMax.x(), bMin.y(), bMin.z()), float3(bMax.x(), bMax.y(), bMin.z()));
																
	DrawLine(float3(bMin.x(), bMin.y(), bMax.z()), float3(bMin.x(), bMax.y(), bMax.z()));
	DrawLine(float3(bMax.x(), bMin.y(), bMax.z()), float3(bMax.x(), bMax.y(), bMax.z()));

}
void Gizmos::Init() {
	/*_backMaterial = Material::Create(Shader::Create(L"shaders/gizmos.fx"), "gizmo_back");

	_frontMaterial = Material::Create(_backMaterial->GetShader(), "gizmo_front");

	_backMaterial->GetParametersBlock().SetValue("alphaMul", 0.2f);
	_frontMaterial->GetParametersBlock().SetValue("alphaMul", 1.0f);

	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	auto vs = _backMaterial->GetShader()->GetShader(ShaderType::Vs);
	auto device = LEngine::Instance()->GetRenderer()->GetDevice();
	auto hr = device->CreateInputLayout(ied, 2, vs->blob->GetBufferPointer(), vs->blob->GetBufferSize(), &_inputLayout);

	D3D11_DEPTH_STENCIL_DESC desc;
	d3d11_helper::DefaultDepthStencilDesc(desc);
	hr = device->CreateDepthStencilState(&desc, &_frontLineDepthState);
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	hr = device->CreateDepthStencilState(&desc, &_backLineDepthState);*/
}
void Gizmos::DrawLine(const float3& from, const float3& to) {
	/*_vertices.push_back(GizmoVertex(lm::mul(_matrix, from), _color));
	_vertices.push_back(GizmoVertex(lm::mul(_matrix, to), _color));*/
}
void Gizmos::DrawAll(CameraPtr camera) {
	/*auto renderer = LEngine::Instance()->GetRenderer();
	
	renderer->GetImmediateContext()->OMSetDepthStencilState(_frontLineDepthState, 0);
	DrawImpl(camera, _frontMaterial);
	renderer->GetImmediateContext()->OMSetDepthStencilState(_backLineDepthState, 0);
	DrawImpl(camera, _backMaterial);
	renderer->GetImmediateContext()->OMSetDepthStencilState(_frontLineDepthState, 0);*/
}
void Gizmos::DrawImpl(CameraPtr camera, MaterialPtr material) {
	/*if (_vertices.size() < 2) {
		return;
	}
	//set system variables
	auto& params = material->GetParametersBlock();
	float4x4 matrix = float4x4::identity();
	params.SetValue("mWorld", matrix);
	params.SetValue("mView", camera->worldToCameraMatrix());
	params.SetValue("mProjection", camera->projectionMatrix());

	auto renderer = LEngine::Instance()->GetRenderer();

	material->Apply(renderer->GetImmediateContext());

	ID3D11Buffer* vb[1] = { _vertexBuffer };
	UINT stride = sizeof(GizmoVertex);
	UINT offset = 0;

	renderer->GetImmediateContext()->IASetInputLayout(_inputLayout);
	renderer->GetImmediateContext()->IASetVertexBuffers(0, 1, vb, &stride, &offset);
	renderer->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	renderer->GetImmediateContext()->Draw(_vertices.size(), 0);*/
}
void Gizmos::Clear() {
	/*_vertices.clear();
	_matrix = float4x4::identity();*/
}
void Gizmos::PrepareRender() {
	/*_vertexBuffer = nullptr;
		
	if (_vertices.size() < 2) {
		return;
	}
	//vertex buffer
	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(_vertices[0])* _vertices.size();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &_vertices[0];
	data.SysMemPitch = 0;

	_vertexBuffer = nullptr;
	LEngine::Instance()->GetRenderer()->GetDevice()->CreateBuffer(&desc, &data, &_vertexBuffer);*/
}
float4 Gizmos::GetColor() {
	return _color;
}
void Gizmos::SetColor(float4 color) {
	_color = color;
}