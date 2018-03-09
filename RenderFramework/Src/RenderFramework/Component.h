#ifndef Component_h__
#define Component_h__

#include <memory>
#include "ObjectsFactory.h"

LOBJECT(Component, Object)
public:
	GameObjectPtr gameObject;
	TransformPtr transform();
	virtual void tick(float deltaTime) {}
	Component(){}

	void serialize(Archive& archive) override;
};



#endif // Component_h__
