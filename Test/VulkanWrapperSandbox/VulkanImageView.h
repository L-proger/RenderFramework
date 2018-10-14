#pragma once

#include "VulkanLogicalDevice.h"

struct VulkanImageViewCreateInfo : VkImageViewCreateInfo {
	VulkanImageViewCreateInfo() {
		this->sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		this->pNext = nullptr;
		this->flags = 0;
	}

	static VulkanImageViewCreateInfo image2D(VkImage image, VkFormat format, uint32_t baseMip = 0, uint32_t mipCount = 1, VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_COLOR_BIT) {
		VulkanImageViewCreateInfo result;
		result.viewType = VK_IMAGE_VIEW_TYPE_2D;
		result.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		result.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		result.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		result.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		result.image = image;
		result.format = format;
		result.subresourceRange.baseArrayLayer = 0;
		result.subresourceRange.layerCount = 1;
		result.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		result.subresourceRange.baseMipLevel = 0;
		result.subresourceRange.levelCount = 1;
		return result;
	}
};

class VulkanImageView {
public:
	VulkanImageView(IntrusivePtr<VulkanLogicalDevice> device, VulkanImageViewCreateInfo createInfo):_device(device){
		if (_device->functions().vkCreateImageView(&createInfo, nullptr, &_native) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image views!");
		}
	}
	~VulkanImageView() {
		_device->functions().vkDestroyImageView(_native, nullptr);
	}
	VkImageView native() const {
		return _native;
	}
private:
	IntrusivePtr<VulkanLogicalDevice> _device;
	VkImageView _native;
};