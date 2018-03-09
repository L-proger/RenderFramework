#ifndef ComponentFactory_h__
#define ComponentFactory_h__

#include "ForwardDeclarations.h"
#include <functional>
#include <map>
#include "Object.h"

class ObjectsFactory {
public:
	typedef std::function<std::shared_ptr<Object>()> factory_function;
	typedef std::map<std::wstring, factory_function> factory_container;

	static ObjectsFactory& instance();
	void register_factory(factory_function factory, const std::wstring& class_name);
	std::shared_ptr<Object> create_object(const std::wstring& class_name) const;

	template<typename T>
	std::shared_ptr<T> create_object(){
		return std::dynamic_pointer_cast<T>(create_object(T::type_name(), game_object));
	}
private:
	factory_container _factory_functions;
};


template<typename T>
struct ObjectFactory {
	typedef std::shared_ptr<T> object_pointer_t;
	ObjectFactory() {
		ObjectsFactory::instance().register_factory(&factory_func, T::type_name());
	}
	static std::shared_ptr<Object> factory_func() {
		return std::static_pointer_cast<Object>(T::create());
	}
};


#define LOBJECT(__type_name, __base_type) \
class __type_name;\
static ObjectFactory<__type_name> __type_name##_factory;\
class __type_name : public __base_type {\
public:\
static std::wstring type_name() {\
return L#__type_name;\
}\
std::wstring get_type_name() const override{\
	return L#__type_name;\
}\
static std::shared_ptr<__type_name> create() {\
	auto result = std::shared_ptr<__type_name>(new __type_name());\
	result->Register();\
	result->construct();\
	return result;\
}


#endif // ComponentFactory_h__
