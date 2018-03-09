#include "Component.h"
#include "GameObject.h"

TransformPtr Component::transform() {
	return gameObject->transform;
}

void Component::serialize(Archive& archive) {
	auto ptr = std::static_pointer_cast<Object>(gameObject);
	archive << ptr;

	if (archive.is_loading()) {
		gameObject = std::static_pointer_cast<GameObject>(ptr);

	}
}


