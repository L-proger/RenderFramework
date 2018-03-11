#pragma once

#include "VulkanLibrary.h"
#include "DynamicLibrary.h"
#include <memory>
#include <vulkan/vulkan.h>

class VulkanDynamicLibrary : public VulkanLibrary {
public:
	VulkanDynamicLibrary(const StdFileSystem::path& path = "vulkan-1") : _library(path) {
		getInstanceProcAddr = _library.getFunction<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");

		#define VK_USE_GLOBAL_FUNCTION(name) _functions.name = reinterpret_cast<PFN_##name>(getInstanceProcAddr(nullptr, #name));
		VK_GLOBAL_FUNCTIONS
		#undef VK_USE_GLOBAL_FUNCTION
	}
	
private:
	DynamicLibrary _library;
};