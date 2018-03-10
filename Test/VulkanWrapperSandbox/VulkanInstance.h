#pragma once

#include <stdexcept>
#include "DynamicLibrary.h"
#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanApplicationInfo.h"

#define VK_GLOBAL_FUNCTIONS \
	VK_USE_GLOBAL_FUNCTION(vkCreateInstance) \
	VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceExtensionProperties) \
	VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceLayerProperties)


#define VK_INSTANCE_FUNCTIONS \
	VK_USE_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices) \
	VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFeatures) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDevice) \
    VK_USE_INSTANCE_FUNCTION(vkGetDeviceProcAddr) \
    VK_USE_INSTANCE_FUNCTION(vkDestroyInstance) \
    VK_USE_INSTANCE_FUNCTION(vkEnumerateDeviceExtensionProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkDestroySurfaceKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceMemoryProperties)

		//    VK_USE_INSTANCE_FUNCTION(vkCreateWin32SurfaceKHR) \

#define VK_DEVICE_FUNCTIONS \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceQueue) \
    VK_USE_DEVICE_FUNCTION(vkDeviceWaitIdle)  \
    VK_USE_DEVICE_FUNCTION(vkDestroyDevice) \
    VK_USE_DEVICE_FUNCTION(vkCreateSemaphore) \
    VK_USE_DEVICE_FUNCTION(vkCreateCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkAllocateCommandBuffers) \
    VK_USE_DEVICE_FUNCTION(vkBeginCommandBuffer) \
    VK_USE_DEVICE_FUNCTION(vkCmdPipelineBarrier) \
    VK_USE_DEVICE_FUNCTION(vkCmdClearColorImage) \
    VK_USE_DEVICE_FUNCTION(vkEndCommandBuffer) \
    VK_USE_DEVICE_FUNCTION(vkQueueSubmit) \
    VK_USE_DEVICE_FUNCTION(vkFreeCommandBuffers) \
    VK_USE_DEVICE_FUNCTION(vkDestroyCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkDestroySemaphore) \
     \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateSwapchainKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkGetSwapchainImagesKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkAcquireNextImageKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkQueuePresentKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroySwapchainKHR) \
     \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateImageView) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateFramebuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateShaderModule) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreatePipelineLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateGraphicsPipelines) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBeginRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBindPipeline) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdDraw) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdEndRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyShaderModule) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyPipelineLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyPipeline) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyFramebuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyImageView) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateFence) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateBuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkGetBufferMemoryRequirements) \
    VK_DEVICE_LEVEL_FUNCTION(vkAllocateMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkBindBufferMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkMapMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkFlushMappedMemoryRanges) \
    VK_DEVICE_LEVEL_FUNCTION(vkUnmapMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdSetViewport) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdSetScissor) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBindVertexBuffers) \
    VK_DEVICE_LEVEL_FUNCTION(vkWaitForFences) \
    VK_DEVICE_LEVEL_FUNCTION(vkResetFences) \
    VK_DEVICE_LEVEL_FUNCTION(vkFreeMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyBuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyFence) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdCopyBuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateImage) \
    VK_DEVICE_LEVEL_FUNCTION(vkGetImageMemoryRequirements) \
    VK_DEVICE_LEVEL_FUNCTION(vkBindImageMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateSampler) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdCopyBufferToImage) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateDescriptorSetLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateDescriptorPool) \
    VK_DEVICE_LEVEL_FUNCTION(vkAllocateDescriptorSets) \
    VK_DEVICE_LEVEL_FUNCTION(vkUpdateDescriptorSets) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBindDescriptorSets) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyDescriptorPool) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyDescriptorSetLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroySampler) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyImage)

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
private:
	PFN_vkGetInstanceProcAddr _getInstanceProcAddr;
	std::unique_ptr<VulkanGlobalFunctions> _globalFunctions;
	std::unique_ptr<VulkanInstanceFunctions> _instanceFunctions;
	DynamicLibrary _library;
	VkInstance _instance = nullptr;
	bool _isValid = false;
};

