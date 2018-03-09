#ifndef Camera_h__
#define Camera_h__

#include "ObjectsFactory.h"
#include <lmath/lmath.h>
#include "Component.h"
using namespace lm;

LOBJECT(Camera, Component)
public:
	float nearClipPlane = 0.03f;
	float farClipPlane = 100.0f;
	float fov = 45.0f;
	float aspect = 1.333333333f;

	virtual void serialize(Archive& archive) override;

	float4x4 worldToCameraMatrix();
	float4x4 projectionMatrix();
	void test() {
		construct();
	}
private:
	float4x4 _projection;
	void UpdateProjectionMatrix();
};

typedef std::shared_ptr<Camera> CameraPtr;
#endif // Camera_h__
