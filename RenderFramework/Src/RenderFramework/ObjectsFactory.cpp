#include "ObjectsFactory.h"


void ObjectsFactory::register_factory(factory_function factory, const std::wstring& class_name) {
	
	_factory_functions[class_name] = factory;
}

ObjectsFactory& ObjectsFactory::instance()
{
	static ObjectsFactory instance;
	return instance;
}

std::shared_ptr<Object> ObjectsFactory::create_object(const std::wstring& class_name) const {
	try {
		return _factory_functions.at(class_name)();
	} catch (...) {
		return nullptr;
	}
}