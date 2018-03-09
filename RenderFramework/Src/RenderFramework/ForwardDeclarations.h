#pragma once

#include <vector>
#include <memory>
#include <lmath/lmath.h>

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectPtr;

class Component;
typedef std::shared_ptr<Component> ComponentPtr;

class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class Transform;
typedef std::shared_ptr<Transform> TransformPtr;

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class Mesh;
typedef std::shared_ptr<Mesh> MeshPtr;

class Material;
typedef std::shared_ptr<Material> MaterialPtr;

class Mouse;
typedef std::shared_ptr<Mouse> MousePtr;

class Keyboard;
typedef std::shared_ptr<Keyboard> KeyboardPtr;

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;