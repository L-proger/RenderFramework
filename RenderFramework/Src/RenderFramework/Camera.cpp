#include "Camera.h"
#include "Transform.h"
#include "Mathf.h"
#include "Archive.h"

float4x4 Camera::worldToCameraMatrix() {
	auto world = transform()->GetGlobalTransform();

	//TODO: why not affine ?
	world = inverse(world, false);

//	auto test = lookatlh(transform()->GetGlobalPosition(), float3(0, 1, 1), float3(0, 1, 0));

	return world;
}



void Camera::serialize(Archive& archive) {
	Component::serialize(archive);
	archive << nearClipPlane << farClipPlane << fov << aspect;
}

void Camera::UpdateProjectionMatrix() {
	_projection = matrix4x4Perspective(fov * Mathf::DegToRad(), aspect, nearClipPlane, farClipPlane);
}

float4x4 Camera::projectionMatrix() {
	UpdateProjectionMatrix();
	return _projection;
}
