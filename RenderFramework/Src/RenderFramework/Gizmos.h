#ifndef Gizmos_h__
#define Gizmos_h__

#include "GizmoVertex.h"
#include <vector>
#include "Material.h"
#include "Shader.h"
#include "d3d11_types.h"

#include <lmath/lmath.h>
#include "Camera.h"
#include "Bounds.h"

using namespace lm;

class Gizmos {
public:
	Gizmos();
	void Init();
	void DrawLine(const float3& from, const float3& to);
	void DrawBounds(const Bounds& bounds);
	void DrawAll(CameraPtr camera);
	void Clear();
	void PrepareRender();
	float4 GetColor();
	void SetColor(float4 color);
	void SetMatrix(const float4x4& matrix);
	float4x4 GetMatrix();
private:
	void DrawImpl(CameraPtr camera, MaterialPtr material);
	ID3D11InputLayoutPtr _inputLayout;
	ID3D11BufferPtr _vertexBuffer;
	ID3D11DepthStencilStatePtr _backLineDepthState;
	ID3D11DepthStencilStatePtr _frontLineDepthState;
	MaterialPtr _backMaterial;
	MaterialPtr _frontMaterial;
	float4 _color;
	float4x4 _matrix;
	std::vector<GizmoVertex> _vertices;
};
#endif // Gizmos_h__
