#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanQueueFamilyProperties.h"
#include "VulkanCommon.h"
#include "IntrusivePtr.h"

class VulkanInstance;

class VulkanPhysicalDevice {
public:
	VulkanPhysicalDevice(const IntrusivePtr<VulkanInstance>& instance, VkPhysicalDevice device);
	VkPhysicalDeviceProperties getProperties() const;
	VkPhysicalDeviceFeatures getFeatures() const;
	std::vector<VulkanQueueFamilyProperties> getQueueFamilyProperties() const;
private:
	IntrusivePtr<VulkanInstance> _instance;
	VkPhysicalDevice _device;
};