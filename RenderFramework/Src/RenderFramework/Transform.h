#ifndef Transform_h__
#define Transform_h__

#include <lmath/lmath.h>
#include "Mathf.h"
#include "ObjectsFactory.h"
#include "Component.h"
#include "Archive.h"

using namespace lm;

LOBJECT(Transform, Component)
public:
	std::shared_ptr<Transform> parent;
	Quaternion_f _rotation;
	float3 _position;
	float3 _scale;

	Transform()
		:_scale(1.0f,1.0f,1.0f), _position(0.0f,0.0f,0.0f), _rotation(0.0f,0.0f,0.0f,1.0f){
	}

	void serialize(Archive& archive) override{
		Component::serialize(archive);
		archive << parent;
		archive << _rotation << _position << _scale;
	}

	std::wstring class_name() const {
		return L"Transform";
	}

	void SetLocalPosition(const float3& position) {
		_position = position;
	}
	float3 GetLocalPosition() {
		return _position;
	}

	float3 forward() const{
		return GetGlobalTransform().z().xyz();
	}

	float3 right() const {
		return GetGlobalTransform().x().xyz();
	}

	float3 up() const {
		return GetGlobalTransform().y().xyz();
	}

	void SetLocalRotation(const Quaternion_f& rotation) {
		_rotation = rotation;
	}

	Quaternion_f GetLocalRotation() {
		return _rotation;
	}

	void SetLocalScale(const float3& scale) {
		_scale = scale;
	}

	float3 GetLocalScale() {
		return _scale;
	}

	float4x4 GetLocalTransform() const{
		auto scaleMatrix = matrix4x4Scale(_scale);
		auto rotationMatrix = matrix4x4RotationQuaternion(_rotation);
		auto positionMatrix = matrix4x4Translation(_position);
		return lm::mul(lm::mul(scaleMatrix, rotationMatrix), positionMatrix);
	}

	float4x4 GetGlobalTransform() const{
		if(parent == nullptr) {
			return GetLocalTransform();
		}
		return lm::mul(GetLocalTransform(), parent->GetGlobalTransform());
	}

	float3 GetGlobalPosition() {
		auto tf = GetGlobalTransform();
		return float3(tf[0][3], tf[1][3], tf[2][3]);
	}

	void RotateLocal(const Quaternion_f& rotation) {
		_rotation = lm::mul(_rotation, rotation);
	}
};



#endif // Transform_h__
