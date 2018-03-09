#ifndef Object_h__
#define Object_h__

#include <cstdint>
#include <string>
#include <fstream>
#include <memory>
#include <windows.h>
#include <functional>
#include <map>
#include <vector>
#include <atomic>
#include "Asset.h"

class Object;
class OutputArchive;

class ObjectRegistry {
public:
	using instance_id_t = uint64_t;
	friend class Object;
private:
	static instance_id_t add_object(std::shared_ptr<Object> object);
	static void remove_object(instance_id_t object);
	static std::map<instance_id_t, std::weak_ptr<Object>> _registry;
	static std::atomic<instance_id_t> _last_index;
};

class Archive;
class Object : public std::enable_shared_from_this<Object>{
public:
	using instance_id_t = ObjectRegistry::instance_id_t;
	virtual void serialize(Archive& archive);

	virtual void construct() {
		
	}

	virtual std::wstring get_type_name() const{
		return L"Object";
	}
	
	std::shared_ptr<Object> as_object(){
		return shared_from_this();
	}

	template<typename T>
	static std::vector<std::shared_ptr<T>> FindObjectsOfType() {
		std::vector<std::shared_ptr<T>> result;
		auto& registry = ObjectRegistry::_registry;
		for(auto& pair : registry){
			auto obj = pair.second.lock();
			auto targetObj = std::dynamic_pointer_cast<T>(obj);
			if(targetObj != nullptr){
				result.push_back(targetObj);
			}
		}
		return result;
	}

	static std::shared_ptr<Object> Find(const AssetFileLink& link)
	{
		auto& registry = ObjectRegistry::_registry;
		for (auto& pair : registry) {
			auto obj = pair.second.lock();
			if(obj != nullptr && obj->GetFileLink() == link)
			{
				return obj;
			}
		}
		return nullptr;
	}

	static std::shared_ptr<Object> create();
	virtual ~Object();

	const std::wstring& get_name() const{
		return _name;
	}

	void SetName(const std::wstring& name){
		_name = name;
	}

	instance_id_t GetInstanceId() const{
		return _instance_id;
	}

	const AssetFileLink& GetFileLink() const{
		return _fileLink;
	}
	void SetLink(const AssetFileLink& link){
		_fileLink = link;
	}
protected:
	void Register();
	Object();
	AssetFileLink _fileLink;
	instance_id_t _instance_id;
private:
	std::wstring _name;
};

#endif // Object_h__
