#include <iostream>

#include <vulkan/vulkan.h>
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#include "DynamicLibrary.h"
#include "VulkanInstance.h"
#include "VulkanDynamicLibrary.h"

int main() {

	auto vulkan = std::make_shared<VulkanDynamicLibrary>();
	auto extensions = vulkan->getSupportedExtensions();
	auto layers = vulkan->getSupportedLayers();

	VulkanApplicationInfo appInfo("Test project", 1, "Test");

	std::vector<std::string> instanceLayers;
	std::vector<std::string> instanceExtensions{
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
	};

	auto instance = vulkan->createInstance(appInfo, 0, instanceLayers, instanceExtensions);
	auto physicalDevices = instance->enumeratePhysicalDevices();
	auto device = physicalDevices[0];

	auto properties = device.getProperties();
	auto features = device.getFeatures();
	auto families = device.getQueueFamilyProperties();

	std::cout << "Test" << std::endl;
}