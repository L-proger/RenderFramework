#ifndef GizmoVertex_h__
#define GizmoVertex_h__

#include <lmath/lmath.h>

using namespace lm;

struct GizmoVertex {
	float4 position;
	float4 color;

	GizmoVertex(float4 _position, float4 _color) 
		:position(_position), color(_color)
	{

	}

	GizmoVertex(float3 _position, float4 _color)
		:position(_position.x(), _position.y(), _position.z(), 1.0f), color(_color)
	{

	}
};
#endif // GizmoVertex_h__
