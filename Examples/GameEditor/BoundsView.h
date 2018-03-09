#ifndef BoundsView_h__
#define BoundsView_h__

#include <RenderFramework/ObjectsFactory.h>

LOBJECT(BoundsView, Component)
public:
	void tick(float deltaTime) override {
		LEngine::Instance()->GetActiveScene()->GetGizmos().SetMatrix(transform()->GetGlobalTransform());
		LEngine::Instance()->GetActiveScene()->GetGizmos().DrawBounds(gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds());
	}
};
#endif // BoundsView_h__
