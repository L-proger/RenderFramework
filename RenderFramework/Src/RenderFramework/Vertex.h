#ifndef Vertex_h__
#define Vertex_h__

#include <lmath/lmath.h>

using namespace lm;
struct Vertex {
	float4 position;
	float3 normal;
	float2 uv0;
	float2 uv1;

	Vertex() {

	}

	Vertex(float4 _pos, float3 _norm) {
		position = _pos;
		normal = _norm;
	}
	Vertex(float4 _pos, float3 _norm, float2 _uv0) {
		position = _pos;
		normal = _norm;
		uv0 = _uv0;
	}
};
#endif // Vertex_h__
