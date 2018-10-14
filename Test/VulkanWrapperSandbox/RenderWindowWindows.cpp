#include "RenderWindow.h"
#include "WindowWindows.h"
#include <memory>
#include <vulkan/vulkan_win32.h>

class RenderWindow::RenderWindowPrivate {
public:
	RenderWindowPrivate(IntrusivePtr<VulkanInstance> instance, const std::string& name):instance(instance) {
		window = std::make_unique<Window>(name);
	}

	~RenderWindowPrivate() {
		auto destroySurfaceKHR = instance->getProcAddr<PFN_vkDestroySurfaceKHR>("vkDestroySurfaceKHR");
		if (destroySurfaceKHR) {
			destroySurfaceKHR(instance->vkInstance(), surface, nullptr);
		}
	}
	std::unique_ptr<Window> window{};
	VkSurfaceKHR surface;
	IntrusivePtr<VulkanInstance> instance;
};

RenderWindow::RenderWindow(IntrusivePtr<VulkanInstance> instance) : RenderWindow(instance, "RenderWindow") {}
RenderWindow::RenderWindow(IntrusivePtr<VulkanInstance> instance, const std::string& name) {
	_private.reset(new RenderWindowPrivate(instance, name));

	VkWin32SurfaceCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = _private->window->getHwnd();
	createInfo.hinstance = GetModuleHandle(nullptr);

	auto createWin32SurfaceKHR = instance->getProcAddr<PFN_vkCreateWin32SurfaceKHR>("vkCreateWin32SurfaceKHR");

	if (!createWin32SurfaceKHR || createWin32SurfaceKHR(instance->vkInstance(), &createInfo, nullptr, &_private->surface) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create render window surface");
	}
}
RenderWindow::~RenderWindow() = default;

std::vector<std::string> RenderWindow::getRequiredExtensionNames(){
	return { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
}

bool RenderWindow::update() {
	return _private->window->update();
}

bool RenderWindow::canPresent(const VulkanPhysicalDevice& physicalDevice, uint32_t queueFamilyIndex) {
	auto func = _private->instance->getProcAddr<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>("vkGetPhysicalDeviceSurfaceSupportKHR");
	if (func == nullptr) {
		return false;
	}
	VkBool32 presentSupported = VK_FALSE;
	func(physicalDevice.getDevice(), queueFamilyIndex, _private->surface, &presentSupported);
	return presentSupported != VK_FALSE;
}
VkSurfaceKHR RenderWindow::getSurface() const {
	return _private->surface;
}