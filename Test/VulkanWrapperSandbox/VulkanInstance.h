#pragma once

#include <stdexcept>
#include "DynamicLibrary.h"
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanApplicationInfo.h"

#include "VulkanFunctions.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLibrary.h"
#include "RefCountedObject.h"


class VulkanInstanceFunctions {
public:
	VulkanInstanceFunctions() {}
	VulkanInstanceFunctions(const VulkanInstance& instance);

#define VK_USE_INSTANCE_FUNCTION(name) PFN_##name name = nullptr;
	VK_INSTANCE_FUNCTIONS
#undef VK_USE_INSTANCE_FUNCTION
};

//TODO: manage external and internal instance creation and destroy instance in destructor if created internally
class VulkanInstance : public RefCountedObject {
public:
	VulkanInstance(IntrusivePtr<VulkanLibrary> library, VkInstance instance) : _library(library),_instance(instance){
		_instanceFunctions = VulkanInstanceFunctions(*this);
		
	}

	const VulkanInstanceFunctions& functions() const {
		return _instanceFunctions;
	}

	VkInstance vkInstance() const {
		return _instance;
	}

	template<typename FunctionPtr, typename = std::enable_if_t<std::is_function_v<std::remove_pointer_t<FunctionPtr>>>>
	auto getProcAddr(const char* name) const {
		return reinterpret_cast<FunctionPtr>(_library->getInstanceProcAddr(_instance, name));
	}

	uint32_t getPhysicalDeviceCount() const {
		uint32_t count = 0;
		if (_instanceFunctions.vkEnumeratePhysicalDevices(_instance, &count, nullptr) != VK_SUCCESS) {
			throw std::runtime_error("Failed to get physical device count");
		}
		return count;
	}

	std::vector<VulkanPhysicalDevice> enumeratePhysicalDevices();

private:
	VulkanInstanceFunctions _instanceFunctions;
	IntrusivePtr<VulkanLibrary> _library;
	VkInstance _instance = nullptr;
};

