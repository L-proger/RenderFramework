#include "Object.h"
#include "Archive.h"

std::map<ObjectRegistry::instance_id_t, std::weak_ptr<Object>> ObjectRegistry::_registry;

std::atomic<ObjectRegistry::instance_id_t> ObjectRegistry::_last_index = 0;

Object::Object():_instance_id(-1){
	
}

std::shared_ptr<Object> Object::create(){
	auto result = std::shared_ptr<Object>(new Object());
	result->Register();
	return result;
}

Object::~Object(){
	ObjectRegistry::remove_object(_instance_id);
}

void Object::Register(){
	_instance_id = ObjectRegistry::add_object(shared_from_this());
}

void Object::serialize(Archive& archive) {
	archive << _name;
}

ObjectRegistry::instance_id_t ObjectRegistry::add_object(std::shared_ptr<Object> object) {
	auto result = _last_index++;
	_registry[result] = object;
	return result;
}

void ObjectRegistry::remove_object(instance_id_t object) {
	_registry.erase(object);
}

