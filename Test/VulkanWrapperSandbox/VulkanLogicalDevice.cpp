#include "VulkanLogicalDevice.h"

VulkanDeviceFunctions::VulkanDeviceFunctions(VulkanLogicalDevice* device) {

#define VK_USE_DEVICE_FUNCTION(name) name = LambdaHelper<RemoveFirstArgT<PFN_##name>>::makeLambda(device->getProcAddr<PFN_##name>(#name), device->getDevice());
	VK_DEVICE_FUNCTIONS
#undef VK_USE_DEVICE_FUNCTION

#define VK_USE_DEVICE_CMD_FUNCTION(name) name = device->getProcAddr<PFN_##name>(#name); 
		VK_DEVICE_CMD_FUNCTIONS
#undef VK_USE_DEVICE_CMD_FUNCTION

#define VK_USE_DEVICE_QUEUE_FUNCTION(name) name = device->getProcAddr<PFN_##name>(#name); 
		VK_DEVICE_QUEUE_FUNCTIONS
#undef VK_USE_DEVICE_QUEUE_FUNCTION
}

VkDevice VulkanLogicalDevice::getDevice() const {
	return _device;
}

const VulkanDeviceFunctions& VulkanLogicalDevice::functions() const {
	return _functions;
}