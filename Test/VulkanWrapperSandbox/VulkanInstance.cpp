#include "VulkanInstance.h"

VulkanGlobalFunctions::VulkanGlobalFunctions(const VulkanInstance& instance) {
#define VK_USE_GLOBAL_FUNCTION(name) name = instance.getInstanceProcAddr<PFN_##name>(nullptr, #name);
	VK_GLOBAL_FUNCTIONS
#undef VK_USE_GLOBAL_FUNCTION
}


VulkanInstanceFunctions::VulkanInstanceFunctions(const VulkanInstance& instance) {
#define VK_USE_INSTANCE_FUNCTION(name) name = instance.getInstanceProcAddr<PFN_##name>(instance.vkInstance(), #name);
	VK_INSTANCE_FUNCTIONS
#undef VK_USE_INSTANCE_FUNCTION
}

std::vector<VulkanPhysicalDevice> VulkanInstance::enumeratePhysicalDevices() const {
	auto deviceCount = getPhysicalDeviceCount();
	std::vector<VkPhysicalDevice> devices(deviceCount);

	if (deviceCount == 0) {
		return {};
	}

	while (true) {

		auto result = _instanceFunctions->vkEnumeratePhysicalDevices(_instance, &deviceCount, &devices[0]);
		if (result == VK_INCOMPLETE) {
			deviceCount = getPhysicalDeviceCount();
		}
		else if (result == VK_SUCCESS) {
			break;
		}
		else {
			throw std::runtime_error("Failed to enumerate physical devices");
		}
	}
	devices.resize(deviceCount);

	std::vector<VulkanPhysicalDevice> result;
	for (auto& device : devices) {
		result.push_back(VulkanPhysicalDevice(*this, device));
	}
	return result;
}