#pragma once

#include <vulkan/vulkan.h>

struct VulkanQueueFamilyProperties : VkQueueFamilyProperties {
	bool isGraphics() const {
		return queueFlags & VK_QUEUE_GRAPHICS_BIT;
	}
	bool isCompute() const {
		return queueFlags & VK_QUEUE_COMPUTE_BIT;
	}
	bool isTransfer() const {
		return queueFlags & VK_QUEUE_TRANSFER_BIT;
	}
	bool isSparseBinding() const {
		return queueFlags & VK_QUEUE_SPARSE_BINDING_BIT;
	}
	bool isProtected() const {
		return queueFlags & VK_QUEUE_PROTECTED_BIT;
	}
};