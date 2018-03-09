#include "Scene.h"
#include "GameObject.h"

void Scene::tick(float deltaTime) {
	for (auto go : objects) {
		go->tick(deltaTime);
	}
}
void Scene::SetName(const std::string& name) {
	_name = name;
}
std::string Scene::GetName() {
	return _name;
}