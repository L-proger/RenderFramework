#ifndef GameObject___h__
#define GameObject___h__

#include "ForwardDeclarations.h"
#include <memory>
#include <vector>
#include <typeinfo>
#include "ObjectsFactory.h"
#include "OutputArchive.h"
#include "Transform.h"

LOBJECT(GameObject, Object)
public:
	TransformPtr transform;

	void tick(float deltaTime);

	virtual void serialize(Archive& archive) override {
		Object::serialize(archive);

		if (archive.is_loading()) {
			components.clear();
			transform = nullptr;
		}

		Archive::size_type cnt = components.size();
		archive << cnt;

		if (archive.is_loading()) {
			for (Archive::size_type i = 0; i < cnt; ++i) {
				std::shared_ptr<Object> obj;
				archive << obj;
				components.push_back(std::static_pointer_cast<Component>(obj));

				auto tp = std::dynamic_pointer_cast<Transform>(obj);
				if (tp != nullptr) {
					transform = tp;
				}
			}
		} else {
			for (auto component : components) {
				auto ptr = std::static_pointer_cast<Object>(component);
				archive << ptr;
			}
		}
	}

	std::shared_ptr<GameObject> as_game_object() {
		return std::static_pointer_cast<GameObject>(shared_from_this());
	}

	template<typename T>
	std::shared_ptr<T> AddComponent() {
		auto component = T::create();
		component->gameObject = as_game_object();
		components.push_back(component);
		return component;
	}

	template<typename T>
	std::shared_ptr<T> GetComponent() {
		for (auto c : components) {
			auto tmp = std::dynamic_pointer_cast<T>(c);
			if (tmp != nullptr) {
				return tmp;
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> GetComponents() {
		std::vector<std::shared_ptr<T>> result;
		for (auto c : components) {
			auto tmp = std::dynamic_pointer_cast<T>(c);
			if (tmp != nullptr) {
				result.push_back(tmp);
			}
		}
		return result;
	}

	void construct() override {
		construct2();
	}
	void construct2();

private:
	GameObject() {}
	std::vector<ComponentPtr> components;
};



#endif // GameObject___h__
