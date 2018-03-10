#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanQueueFamilyProperties.h"

class VulkanInstance;

class VulkanPhysicalDevice {
public:
	VulkanPhysicalDevice(const VulkanInstance& instance, VkPhysicalDevice device):_instance(instance), _device(device) {}
	VkPhysicalDeviceProperties getProperties() const;
	VkPhysicalDeviceFeatures getFeatures() const;
	std::vector<VulkanQueueFamilyProperties> getQueueFamilyProperties() const;
private:
	const VulkanInstance& _instance;
	VkPhysicalDevice _device;
};