#include "VulkanLibrary.h"
#include "VulkanInstance.h"

IntrusivePtr<VulkanInstance> VulkanLibrary::createInstance(const VulkanApplicationInfo& info, VkInstanceCreateFlags flags, const std::vector<std::string>& layers, const std::vector<std::string>& extensions, VkAllocationCallbacks* allocCallbacks) {

	std::vector<const char*> _extensions;
	for (auto& ext : extensions) {
		_extensions.push_back(ext.c_str());
	}

	std::vector<const char*> _layers;
	for (auto& layer : layers) {
		_layers.push_back(layer.c_str());
	}

	VkInstanceCreateInfo instance_create_info = {
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		nullptr,
		flags,
		&info,
		static_cast<uint32_t>(_layers.size()),
		(_layers.size() == 0 ? nullptr : &_layers[0]),
		static_cast<uint32_t>(_extensions.size()),
		(_extensions.size() == 0 ? nullptr : &_extensions[0])
	};

	VkInstance instance;
	if (_functions.vkCreateInstance(&instance_create_info, allocCallbacks, &instance) != VK_SUCCESS) {
		return nullptr;
	}

	return new VulkanInstance(this, instance);
}