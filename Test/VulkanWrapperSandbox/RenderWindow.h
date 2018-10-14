#pragma once

#include "VulkanInstance.h"
#include "IntrusivePtr.h"
#include <vector>

class RenderWindow {
public:
	RenderWindow(IntrusivePtr<VulkanInstance> instance);
	RenderWindow(IntrusivePtr<VulkanInstance> instance, const std::string& name);
	~RenderWindow();
	static std::vector<std::string> getRequiredExtensionNames();
	bool update();
	bool canPresent(const VulkanPhysicalDevice& physicalDevice, uint32_t queueFamilyIndex);
	VkSurfaceKHR getSurface() const;
private:
	class RenderWindowPrivate;
	std::unique_ptr<RenderWindowPrivate> _private{};
};