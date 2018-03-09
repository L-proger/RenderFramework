#ifndef Bounds_h__
#define Bounds_h__

#include <lmath/lmath.h>
using namespace lm;

class Bounds {
public:
	Bounds() 
		:_center(0.0f,0.0f,0.0f), _size(0.0f,0.0f,0.0f) {

	}
	Bounds(float3 center, float3 size) 
		:_center(center), _size(size)
	{

	}
	
	float3 GetSize() {
		return _size;
	}
	float3 GetCenter() {
		return _center;
	}
	void SetSize(const float3& size) {
		_size = size;
	}
	void SetCenter(const float3& center) {
		_center = center;
	}
	void Scale(float value) {
		_size *= value;
	}
	float3 Minimum() const {
		return _size * -0.5f + _center;
	}
	float3 Maximum() const {
		return _size * 0.5f + _center;
	}
private:
	float3 _center;
	float3 _size;
};
#endif // Bounds_h__
