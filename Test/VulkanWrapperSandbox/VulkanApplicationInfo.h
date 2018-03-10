#pragma once

#include <vulkan/vulkan.h>

struct VulkanApplicationInfo : public VkApplicationInfo {
	VulkanApplicationInfo(const char* pApplicationName_ = nullptr, uint32_t applicationVersion_ = 0, const char* pEngineName_ = nullptr, uint32_t engineVersion_ = 0, uint32_t apiVersion_ = 0) {
		sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		pNext = nullptr;
		pApplicationName = pApplicationName_;
		applicationVersion = applicationVersion_;
		pEngineName = pEngineName_;
		engineVersion = engineVersion_;
		apiVersion = apiVersion_;
	}
};