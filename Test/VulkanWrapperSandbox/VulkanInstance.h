#pragma once

#include <stdexcept>
#include "DynamicLibrary.h"
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanApplicationInfo.h"

#include "VulkanFunctions.h"
#include "VulkanPhysicalDevice.h"

class VulkanInstance;

class VulkanGlobalFunctions {
public:
	VulkanGlobalFunctions(const VulkanInstance& instance);

#define VK_USE_GLOBAL_FUNCTION(name) PFN_##name name;
	VK_GLOBAL_FUNCTIONS
#undef VK_USE_GLOBAL_FUNCTION
};

class VulkanInstanceFunctions {
public:
	VulkanInstanceFunctions(const VulkanInstance& instance);

#define VK_USE_INSTANCE_FUNCTION(name) PFN_##name name;
	VK_INSTANCE_FUNCTIONS
#undef VK_USE_INSTANCE_FUNCTION
};

class VulkanInstance {
public:
	VulkanInstance():_library("vulkan-1"){
		_getInstanceProcAddr = _library.getFunction<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");

		_globalFunctions.reset(new VulkanGlobalFunctions(*this));
	}

	template<typename FunctionPtr, typename = std::enable_if_t<std::is_function_v<std::remove_pointer_t<FunctionPtr>>>>
	auto getInstanceProcAddr(VkInstance instance, const char* name) const {
		return reinterpret_cast<FunctionPtr>(_getInstanceProcAddr(instance, name));
	}

	auto getInstanceProcAddr(VkInstance instance, const char* name) const {
		return _getInstanceProcAddr(instance, name);
	}

	const VulkanGlobalFunctions* getGlobalFunctions() const {
		return _globalFunctions.get();
	}

	const VulkanInstanceFunctions* getInstanceFunctions() const {
		return _instanceFunctions.get();
	}

	std::vector<VkExtensionProperties> getSupportedExtensions(const char* layerName = nullptr) const {
		uint32_t count = 0;
		if ((_globalFunctions->vkEnumerateInstanceExtensionProperties(layerName, &count, nullptr) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate extensions");
		}

		std::vector<VkExtensionProperties> result(count);
		if ((_globalFunctions->vkEnumerateInstanceExtensionProperties(layerName, &count, &result[0]) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate extensions");
		}

		return result;
	}

	std::vector<VkLayerProperties> getSupportedLayers() const {
		uint32_t count = 0;
		if ((_globalFunctions->vkEnumerateInstanceLayerProperties(&count, nullptr) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate layers");
		}

		std::vector<VkLayerProperties> result(count);
		if ((_globalFunctions->vkEnumerateInstanceLayerProperties(&count, &result[0]) != VK_SUCCESS)) {
			throw std::runtime_error("Failed to enumerate layers");
		}

		return result;
	}

	bool isValid() const {
		return _isValid;
	}

	bool create(const VulkanApplicationInfo& info, VkInstanceCreateFlags flags, const std::vector<std::string>& layers, const std::vector<std::string>& extensions, VkAllocationCallbacks* allocCallbacks = nullptr) {
		if (isValid()) {
			return true;
		}

		std::vector<const char*> _extensions;
		for (auto& ext : extensions) {
			_extensions.push_back(ext.c_str());
		}

		std::vector<const char*> _layers;
		for (auto& layer : layers) {
			_layers.push_back(layer.c_str());
		}

		VkInstanceCreateInfo instance_create_info = {
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,        
			nullptr,                                      
			flags,
			&info,                            
			static_cast<uint32_t>(_layers.size()),
			(_layers.size() == 0 ? nullptr : &_layers[0]),
			static_cast<uint32_t>(_extensions.size()),
			(_extensions.size() == 0 ? nullptr : &_extensions[0])
		};

		if (_globalFunctions->vkCreateInstance(&instance_create_info, allocCallbacks, &_instance) != VK_SUCCESS) {
			return false;
		}

		_instanceFunctions.reset(new VulkanInstanceFunctions(*this));

		_isValid = true;
		return true;
	}

	VkInstance vkInstance() const {
		return _instance;
	}

	uint32_t getPhysicalDeviceCount() const {
		if (!_isValid) {
			throw std::runtime_error("Instance is not yet created");
		}
		uint32_t count = 0;
		if (_instanceFunctions->vkEnumeratePhysicalDevices(_instance, &count, nullptr) != VK_SUCCESS) {
			throw std::runtime_error("Failed to get physical device count");
		}
		return count;
	}

	std::vector<VulkanPhysicalDevice> enumeratePhysicalDevices() const;
private:
	PFN_vkGetInstanceProcAddr _getInstanceProcAddr;
	std::unique_ptr<VulkanGlobalFunctions> _globalFunctions;
	std::unique_ptr<VulkanInstanceFunctions> _instanceFunctions;
	DynamicLibrary _library;
	VkInstance _instance = nullptr;
	bool _isValid = false;
};

