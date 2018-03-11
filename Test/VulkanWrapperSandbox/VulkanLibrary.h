#pragma once

#include <vulkan/vulkan.h>
#include "VulkanFunctions.h"
#include "VulkanCommon.h"
#include "VulkanApplicationInfo.h"
#include <vector>
#include <memory>

#include "RefCountedObject.h"

class VulkanInstance;

class VulkanGlobalFunctions {
public:
#define VK_USE_GLOBAL_FUNCTION(name) PFN_##name name;
	VK_GLOBAL_FUNCTIONS
#undef VK_USE_GLOBAL_FUNCTION
};

class VulkanLibrary : public RefCountedObject {
public:
	VulkanLibrary() {
		
	}

	const VulkanGlobalFunctions& functions() const {
		return _functions;
	}

	std::vector<VkExtensionProperties> getSupportedExtensions(const char* layerName = nullptr) const {
		uint32_t count = 0;
		if ((_functions.vkEnumerateInstanceExtensionProperties(layerName, &count, nullptr) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate extensions");
		}

		std::vector<VkExtensionProperties> result(count);
		if ((_functions.vkEnumerateInstanceExtensionProperties(layerName, &count, &result[0]) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate extensions");
		}

		return result;
	}

	std::vector<VkLayerProperties> getSupportedLayers() const {
		uint32_t count = 0;
		if ((_functions.vkEnumerateInstanceLayerProperties(&count, nullptr) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate layers");
		}

		std::vector<VkLayerProperties> result(count);
		if ((_functions.vkEnumerateInstanceLayerProperties(&count, &result[0]) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate layers");
		}

		return result;
	}

	IntrusivePtr<VulkanInstance> createInstance(const VulkanApplicationInfo& info, VkInstanceCreateFlags flags, const std::vector<std::string>& layers, const std::vector<std::string>& extensions, VkAllocationCallbacks* allocCallbacks = nullptr);

	PFN_vkGetInstanceProcAddr getInstanceProcAddr;
protected:
	VulkanGlobalFunctions _functions;
};