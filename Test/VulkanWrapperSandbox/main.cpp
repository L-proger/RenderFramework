#include <iostream>

#include <vulkan/vulkan.h>
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#include "DynamicLibrary.h"
#include "VulkanInstance.h"

int main() {
	//PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance"); //works

	VulkanInstance instance;

	auto globalFuncs = instance.getGlobalFunctions();
	auto extensions = instance.getSupportedExtensions();
	auto layers = instance.getSupportedLayers();

	VulkanApplicationInfo appInfo("Test project", 1, "Test");

	std::vector<std::string> instanceLayers;
	std::vector<std::string> instanceExtensions{
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
	};


	instance.create(appInfo, 0, instanceLayers, instanceExtensions);

	auto instanceFuncs = instance.getInstanceFunctions();

	auto physicalDevices = instance.enumeratePhysicalDevices();

	auto device = physicalDevices[0];

	auto properties = device.getProperties();
	auto features = device.getFeatures();
	auto families = device.getQueueFamilyProperties();

	PFN_vkCreateDevice()

	std::cout << "Test" << std::endl;
}