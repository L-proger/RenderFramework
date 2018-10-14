#pragma once
#include <type_traits>
#include <stdexcept>

template<typename T>
void IntrusivePtrAddRef(T* ptr) {
	ptr->addref();
}

template<typename T>
void IntrusivePtrRelease(T* ptr) {
	ptr->release();
}

template<typename Object>
class IntrusivePtr {
public:
	IntrusivePtr() {
	}
	~IntrusivePtr() {
		reset();
	}

	template<typename U>
	IntrusivePtr(U* src, bool addref = true) : _object(static_cast<std::add_pointer_t<std::enable_if_t<std::is_convertible_v<U, Object>, Object>>>(src)) {
		if (addref) {
			addrefImpl();
		}
	}

	template<typename U>
	IntrusivePtr(const IntrusivePtr<U>& src) : _object(static_cast<std::add_pointer_t<std::enable_if_t<std::is_convertible_v<U, Object>, Object>>>(src.get())) {
		addrefImpl();
	}

	IntrusivePtr(Object* object, bool addref = true) :_object(object) {
		if (addref) {
			addrefImpl();
		}
	}
	IntrusivePtr(const IntrusivePtr& ptr) {
		_object = ptr._object;
		if (_object) {
			addrefImpl();
		}
	}
	IntrusivePtr& operator=(const IntrusivePtr& other) {
		assign(other._object, true);
		return *this;
	}
	IntrusivePtr& operator=(std::nullptr_t) {
		reset();
		return *this;
	}

	void assign(Object* object, bool addref = true) {
		if (object != nullptr && addref) {
			object->addref(object);
		}
		reset();
		_object = object;
	}

	Object* operator->() {
		if (_object == nullptr) {
			throw new std::runtime_error("Accessing null object in IntrusivePtr");
		}
		return _object;
	}

	const Object* operator->() const {
		if (_object == nullptr) {
			throw new std::runtime_error("Accessing null object in IntrusivePtr");
		}
		return _object;
	}

	void reset() {
		if (_object != nullptr) {
			releaseImpl();
			_object = nullptr;
		}
	}

	Object* get() const {
		return _object;
	}

private:
	Object * _object = nullptr;

	void addrefImpl() {
		IntrusivePtrAddRef(_object);
	}

	void releaseImpl() {
		IntrusivePtrRelease(_object);
	}
};
