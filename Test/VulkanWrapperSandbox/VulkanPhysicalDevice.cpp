#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(const IntrusivePtr<VulkanInstance>& instance, VkPhysicalDevice device) :_instance(instance), _device(device) {
}

VkPhysicalDeviceProperties VulkanPhysicalDevice::getProperties() const {
	VkPhysicalDeviceProperties result;
	_instance->functions().vkGetPhysicalDeviceProperties(_device, &result);
	return result;
}
VkPhysicalDeviceFeatures VulkanPhysicalDevice::getFeatures() const {
	VkPhysicalDeviceFeatures result;
	_instance->functions().vkGetPhysicalDeviceFeatures(_device, &result);
	return result;
}

std::vector<VulkanQueueFamilyProperties> VulkanPhysicalDevice::getQueueFamilyProperties() const {
	uint32_t count = 0;
	_instance->functions().vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, nullptr);

	if (count == 0) {
		return {};
	}

	std::vector<VulkanQueueFamilyProperties> result(count);
	_instance->functions().vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, &result[0]);
	return result;
}