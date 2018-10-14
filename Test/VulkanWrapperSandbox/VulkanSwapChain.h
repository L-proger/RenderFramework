#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanInstance.h"
#include "VulkanLogicalDevice.h"

class VulkanSwapChain {
public:
	VulkanSwapChain(IntrusivePtr<VulkanLogicalDevice> device, VkSwapchainCreateInfoKHR createInfo):_device(device) {
		if (device->functions().vkCreateSwapchainKHR(&createInfo, nullptr, &_swapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}
		uint32_t imageCount = 0;
		device->functions().vkGetSwapchainImagesKHR(_swapChain, &imageCount, nullptr);
		_images.resize(imageCount);
		device->functions().vkGetSwapchainImagesKHR(_swapChain, &imageCount, _images.data());

		_format = createInfo.imageFormat;
		_extent = createInfo.imageExtent;
	}

	static std::vector<VkSurfaceFormatKHR> getSurfaceFormats(VulkanPhysicalDevice device, VkSurfaceKHR surface) {
		uint32_t formatCount;
		std::vector<VkSurfaceFormatKHR> result;

		device.getInstance()->functions().vkGetPhysicalDeviceSurfaceFormatsKHR(device.getDevice(), surface, &formatCount, nullptr);

		if (formatCount != 0) {
			result.resize(formatCount);
			device.getInstance()->functions().vkGetPhysicalDeviceSurfaceFormatsKHR(device.getDevice(), surface, &formatCount, result.data());
		}
		return result;
	}

	static VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VulkanPhysicalDevice device, VkSurfaceKHR surface) {
		VkSurfaceCapabilitiesKHR result{};
		device.getInstance()->functions().vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.getDevice(), surface, &result);
		return result;
	}

	static std::vector<VkPresentModeKHR> getPresentModes(VulkanPhysicalDevice device, VkSurfaceKHR surface) {
		std::vector<VkPresentModeKHR> result;
		uint32_t presentModeCount = 0;
		device.getInstance()->functions().vkGetPhysicalDeviceSurfacePresentModesKHR(device.getDevice(), surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			result.resize(presentModeCount);
			device.getInstance()->functions().vkGetPhysicalDeviceSurfacePresentModesKHR(device.getDevice(), surface, &presentModeCount, result.data());
		}
		return result;
	}
	VkSwapchainKHR native() const {
		return _swapChain;
	}
	const std::vector<VkImage>& images() const {
		return _images;
	}
	VkFormat format() const {
		return _format;
	}
	VkExtent2D extent() const {
		return _extent;
	}
private:
	IntrusivePtr<VulkanLogicalDevice> _device;
	VkSwapchainKHR _swapChain = {};
	std::vector<VkImage> _images;
	VkFormat _format;
	VkExtent2D _extent;
};