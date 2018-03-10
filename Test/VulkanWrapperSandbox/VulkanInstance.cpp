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