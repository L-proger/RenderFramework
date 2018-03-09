#ifndef Scene_h__
#define Scene_h__

#include <vector>

#include "ForwardDeclarations.h"
#include <string>
#include "Gizmos.h"

class Scene {
public:
	Scene() {
		_gizmos.Init();
	}
	std::vector<GameObjectPtr> objects;
	void tick(float deltaTime);
	void SetName(const std::string& name);
	std::string GetName();
	Gizmos& GetGizmos() {
		return _gizmos;
	}
private:
	Gizmos _gizmos;
	std::string _name;
};
#endif // Scene_h__
