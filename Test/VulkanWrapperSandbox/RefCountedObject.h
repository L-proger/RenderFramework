#pragma once

#include "IntrusivePtr.h"

class RefCountedObject {
public:
	virtual ~RefCountedObject() = default;
	void addref() {
		++_refCount;
	}
	void release() {
		if (--_refCount == 0) {
			delete this;
		}
	}
private:
	size_t _refCount = 0;
};
