#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"

VkPhysicalDeviceProperties VulkanPhysicalDevice::getProperties() const {
	VkPhysicalDeviceProperties result;
	_instance.getInstanceFunctions()->vkGetPhysicalDeviceProperties(_device, &result);
	return result;
}
VkPhysicalDeviceFeatures VulkanPhysicalDevice::getFeatures() const {
	VkPhysicalDeviceFeatures result;
	_instance.getInstanceFunctions()->vkGetPhysicalDeviceFeatures(_device, &result);
	return result;
}

std::vector<VulkanQueueFamilyProperties> VulkanPhysicalDevice::getQueueFamilyProperties() const {
	uint32_t count = 0;
	_instance.getInstanceFunctions()->vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, nullptr);

	if (count == 0) {
		return {};
	}

	std::vector<VulkanQueueFamilyProperties> result(count);
	_instance.getInstanceFunctions()->vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, &result[0]);
	return result;
}