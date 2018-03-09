#ifndef Archive_h__
#define Archive_h__


#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include "Asset.h"
#include <lmath/lmath.h>
#include <type_traits>
#include "Object.h"
#include <cstdint>
#define POD_SERIALIZE(_type) Archive& operator << (_type& value) { serialize(&value, sizeof(value)); return *this; }

class Object;
class Archive {
public:
	typedef uint64_t size_type;
	std::function<void(std::shared_ptr<Object>)> SaveReferenceCallback;
	std::function<std::shared_ptr<Object>(const AssetFileLink&)> LoadReferenceCallback;

	Archive():SaveReferenceCallback(nullptr){
		
	}
	virtual ~Archive() {}
	virtual bool is_loading() const = 0;
	virtual void serialize(void* data, size_t size) = 0;

	virtual size_type get_offset() const = 0;
	virtual void set_offset(size_type offset) = 0;

	virtual void flush() {}

	POD_SERIALIZE(uint8_t);
	POD_SERIALIZE(uint16_t);
	POD_SERIALIZE(uint32_t);
	POD_SERIALIZE(uint64_t);
	POD_SERIALIZE(int8_t);
	POD_SERIALIZE(int16_t);
	POD_SERIALIZE(int32_t);
	POD_SERIALIZE(int64_t);
	POD_SERIALIZE(float);
	POD_SERIALIZE(double);
	POD_SERIALIZE(lm::float2);
	POD_SERIALIZE(lm::float3);
	POD_SERIALIZE(lm::float4);
	POD_SERIALIZE(lm::double2);
	POD_SERIALIZE(lm::double3);
	POD_SERIALIZE(lm::double4);

	POD_SERIALIZE(lm::Quaternion_f);

	Archive& operator << (std::string& value) {
		uint32_t string_len = 0;
		if (is_loading()) {
			serialize(&string_len, sizeof(string_len));
			value.resize(string_len);
			serialize(&value[0], string_len);
		} else {
			string_len = value.size();
			serialize(&string_len, sizeof(string_len));
			serialize(&value[0], string_len);
		}
		return *this;
	}

	Archive& operator << (std::wstring& value) {
		uint32_t string_len = 0;
		if (is_loading()) {
			serialize(&string_len, sizeof(string_len));
			value.resize(string_len);
			serialize(&value[0], string_len * sizeof(std::wstring::value_type));
		} else {
			string_len = value.size();
			serialize(&string_len, sizeof(string_len));
			serialize(&value[0], string_len * sizeof(std::wstring::value_type));
		}
		return *this;
	}

	template<typename T, typename = typename std::enable_if<std::is_base_of<Object, T>::value>::type>
	Archive& operator << (std::shared_ptr<T>& value) {
		if (is_loading()) {
			AssetFileLink link;
			(*this) << link;
			if(link.localId == -1)
			{
				value = nullptr;
			}else
			{
				auto pos = get_offset();
				value = LoadReferenceCallback == nullptr ? nullptr : std::dynamic_pointer_cast<T>(LoadReferenceCallback(link));
				set_offset(pos);
			}
			
		} else {
			if (SaveReferenceCallback != nullptr) {
				SaveReferenceCallback(value);
			}
			AssetFileLink link = value == nullptr ? AssetFileLink() : value->GetFileLink();
			(*this) << link;
		}
		return *this;
	}
private:
	Archive& operator << (AssetFileLink& value);
};
#endif // Archive_h__
