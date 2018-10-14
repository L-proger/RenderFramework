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
	uint32_t count = getQueueFamiliesCount();
	if (count == 0) {
		return {};
	}

	std::vector<VulkanQueueFamilyProperties> result(count);
	_instance->functions().vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, &result[0]);
	return result;
}

std::vector<VkExtensionProperties> VulkanPhysicalDevice::getExtensions(const char* layerName) const {
	uint32_t extensionCount;
	_instance->functions().vkEnumerateDeviceExtensionProperties(_device, layerName, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	_instance->functions().vkEnumerateDeviceExtensionProperties(_device, layerName, &extensionCount, availableExtensions.data());
	return availableExtensions;
}

uint32_t VulkanPhysicalDevice::getQueueFamiliesCount() const {
	uint32_t count = 0;
	_instance->functions().vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, nullptr);
	return count;
}

VkPhysicalDevice VulkanPhysicalDevice::getDevice() const {
	return _device;
}

IntrusivePtr<VulkanInstance> VulkanPhysicalDevice::getInstance() const {
	return _instance;
}