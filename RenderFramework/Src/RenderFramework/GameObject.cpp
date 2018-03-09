
#include "Transform.h"
#include "LEngine.h"
#include "Component.h"
#include "GameObject.h"

void GameObject::tick(float deltaTime) {
	for (auto c : components) {
		c->tick(deltaTime);
	}
}

void GameObject::construct2() {
	Object::construct();
	auto this_ptr = std::static_pointer_cast<GameObject>(shared_from_this());
	LEngine::Instance()->GetActiveScene()->objects.push_back(this_ptr);
	this_ptr->transform = this_ptr->AddComponent<Transform>();
}