#pragma once

#include "VulkanLogicalDevice.h"

class VulkanShaderModule {
public:
	VulkanShaderModule(IntrusivePtr<VulkanLogicalDevice> device, const void* bytecode, uint32_t bytecodeSize):_device(device) {
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = bytecodeSize;
		createInfo.pCode = reinterpret_cast<const uint32_t*>(bytecode);
		if (device->functions().vkCreateShaderModule(&createInfo, nullptr, &_shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}
	}
	~VulkanShaderModule(){
		_device->functions().vkDestroyShaderModule(_shaderModule, nullptr);
	}
private:
	IntrusivePtr<VulkanLogicalDevice> _device;
	VkShaderModule _shaderModule;
};