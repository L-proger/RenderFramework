#include <iostream>

#include <vulkan/vulkan.h>
#include <Windows.h>
#include "DynamicLibrary.h"
#include "VulkanInstance.h"
#include "VulkanDynamicLibrary.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSwapChain.h"
#include "VulkanImageView.h"
#include "VulkanShaderModule.h"
#include "RenderWindow.h"
#include "TempFile.h"
#include "ShaderCompiler.h"
#include <chrono>
#include <thread>

const char* vert = R"(
	#version 450
	#extension GL_ARB_separate_shader_objects : enable

	out gl_PerVertex {
		vec4 gl_Position;
	};

	layout(location = 0) out vec3 fragColor;

	vec2 positions[3] = vec2[](
		vec2(0.0, -0.5),
		vec2(0.5, 0.5),
		vec2(-0.5, 0.5)
	);

	vec3 colors[3] = vec3[](
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);

	void main() {
		gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
		fragColor = colors[gl_VertexIndex];
	}
)";

const char* frag = R"(
	#version 450
	#extension GL_ARB_separate_shader_objects : enable

	layout(location = 0) in vec3 fragColor;

	layout(location = 0) out vec4 outColor;

	void main() {
		outColor = vec4(fragColor, 1.0);
	}
)";

int main() {
	
	auto vulkan = std::make_shared<VulkanDynamicLibrary>();
	auto extensions = vulkan->getSupportedExtensions();
	auto layers = vulkan->getSupportedLayers();

	VulkanApplicationInfo appInfo("Test project", 1, "Test");

	std::vector<std::string> instanceLayers;

	auto instance = vulkan->createInstance(appInfo, 0, instanceLayers, RenderWindow::getRequiredExtensionNames());

	auto physicalDevices = instance->enumeratePhysicalDevices();
	auto device = physicalDevices[0];

	auto properties = device.getProperties();
	auto features = device.getFeatures();
	auto families = device.getQueueFamilyProperties();
	
	RenderWindow window(instance, "VulkanWrapperSandbox");

	std::cout << "Device queue families count: " << device.getQueueFamiliesCount() << std::endl;

	//Find queues
	uint32_t presentQueueIndex = -1;
	uint32_t renderQueueIndex = -1;
	for (uint32_t i = 0; i < device.getQueueFamiliesCount(); ++i) {
		if (presentQueueIndex == -1 && families[i].queueCount > 0 && window.canPresent(device, i)) {
			presentQueueIndex = i;
			std::cout << "Found present queue: " << i << std::endl;
		}

		if (renderQueueIndex == -1 && families[i].isGraphics() && families[i].queueCount > 0) {
			std::cout << "Found render queue: " << i << std::endl;
			renderQueueIndex = i;
		}

		if (renderQueueIndex != -1 && presentQueueIndex != -1) {
			break;
		}
	}

	std::vector<VulkanQueueCreateInfo> queues;
	queues.push_back(VulkanQueueCreateInfo(presentQueueIndex, { 1.0f }));
	if (presentQueueIndex != renderQueueIndex) {
		queues.push_back(VulkanQueueCreateInfo(renderQueueIndex, { 1.0f }));
	}

	auto deviceExtensions = device.getExtensions();

	std::vector<const char*> requiredDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	auto swapChainExt = std::find_if(deviceExtensions.begin(), deviceExtensions.end(), [&requiredDeviceExtensions](VkExtensionProperties ext) { return std::string(requiredDeviceExtensions[0]) == ext.extensionName; });
	if (swapChainExt == deviceExtensions.end()) {
		throw std::runtime_error("Failed to find device with swap chain extension");
	}

	auto formats = VulkanSwapChain::getSurfaceFormats(device, window.getSurface());
	auto caps = VulkanSwapChain::getSurfaceCapabilities(device, window.getSurface());
	auto presentModes = VulkanSwapChain::getPresentModes(device, window.getSurface());

	IntrusivePtr<VulkanLogicalDevice> logicalDevice = IntrusivePtr<VulkanLogicalDevice>(new VulkanLogicalDevice(device, requiredDeviceExtensions, {}, queues));

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.surface = window.getSurface();
	createInfo.imageFormat = formats[0].format;
	createInfo.imageColorSpace = formats[0].colorSpace;
	createInfo.minImageCount = caps.minImageCount+1;
	createInfo.imageExtent = caps.currentExtent;
	createInfo.preTransform = caps.currentTransform;
	createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	std::vector<uint32_t> swapChainQueueFamilies;
	swapChainQueueFamilies.push_back(renderQueueIndex);
	swapChainQueueFamilies.push_back(presentQueueIndex);

	if (presentQueueIndex == renderQueueIndex) {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = &swapChainQueueFamilies[0];
	}
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;


	auto swapChain = new VulkanSwapChain(logicalDevice, createInfo);
	//logicalDevice->functions().vkGetDeviceQueue()

	std::vector<std::shared_ptr<VulkanImageView>> imageViews;
	for (auto image : swapChain->images()) {
		imageViews.push_back(std::make_shared<VulkanImageView>(logicalDevice, VulkanImageViewCreateInfo::image2D(image, swapChain->format())));
	}

	auto vertexBinary = ShaderCompiler::compile(vert, ShaderCompilerStage::vert);
	auto fragmentBinary = ShaderCompiler::compile(frag, ShaderCompilerStage::frag);

	while (window.update()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	std::cout << "Test" << std::endl;
}