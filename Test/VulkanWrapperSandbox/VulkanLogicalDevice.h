#pragma once

#include <vulkan/vulkan.h>
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include <vector>
#include <stdexcept>
#include "VulkanFunctions.h"
#include "RefCountedObject.h"
#include "FunctionTraits.h"

class VulkanQueueCreateInfo {
public:
	uint32_t familyIndex;
	std::vector<float> priorities;
	VulkanQueueCreateInfo(uint32_t familyIndex, const std::vector<float>& priorities):familyIndex(familyIndex), priorities(priorities) {}
};

class VulkanLogicalDevice;

struct VulkanDeviceFunctions {
#define VK_USE_DEVICE_FUNCTION(name) std::function<RemoveFirstArgT<PFN_##name>> name; 
	VK_DEVICE_FUNCTIONS
#undef VK_USE_DEVICE_FUNCTION

#define VK_USE_DEVICE_CMD_FUNCTION(name) PFN_##name name; 
		VK_DEVICE_CMD_FUNCTIONS
#undef VK_USE_DEVICE_CMD_FUNCTION

#define VK_USE_DEVICE_QUEUE_FUNCTION(name) PFN_##name name; 
		VK_DEVICE_QUEUE_FUNCTIONS
#undef VK_USE_DEVICE_QUEUE_FUNCTION

	VulkanDeviceFunctions() = default;
	VulkanDeviceFunctions(VulkanLogicalDevice* device);
};


class VulkanQueue {
public:
	uint32_t familyID;
	uint32_t id;
	VkQueue queue;

	VulkanQueue(uint32_t familyID, uint32_t id, VkQueue queue) :familyID(familyID), id(id), queue(queue) {

	}
private:
	
};

class VulkanLogicalDevice : public RefCountedObject {
public:
	VulkanLogicalDevice(VulkanPhysicalDevice physicalDevice, const std::vector<const char*> extensions, const std::vector<const char*> layers, const std::vector<VulkanQueueCreateInfo>& queues) :_physicalDevice(physicalDevice){
		
		VkPhysicalDeviceFeatures deviceFeatures = {};

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfo;
		queueCreateInfo.reserve(queues.size());

		for (auto& queue : queues) {
			VkDeviceQueueCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			info.pNext = nullptr;
			info.flags = 0;
			info.queueFamilyIndex = queue.familyIndex;
			if (queue.priorities.size() == 0) {
				throw std::runtime_error("Could not create VkDeviceQueueCreateInfo with zero queues");
			}

			for (auto priority : queue.priorities) {
				if (priority < 0.0f || priority > 1.0f) {
					throw std::runtime_error("Could not create VkDeviceQueueCreateInfo! Invalid priority set.");
				}
			}

			info.pQueuePriorities = queue.priorities.data();
			info.queueCount = static_cast<uint32_t>(queue.priorities.size());

			queueCreateInfo.push_back(info);
		}


		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfo.size());
		createInfo.pQueueCreateInfos = queueCreateInfo.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.size() == 0 ? nullptr : extensions.data();
		createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
		createInfo.ppEnabledLayerNames = layers.size() == 0 ? nullptr : layers.data();

		if (physicalDevice.getInstance()->functions().vkCreateDevice(physicalDevice.getDevice(), &createInfo, nullptr, &_device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}

		_getDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(_physicalDevice.getInstance()->getProcAddr<PFN_vkGetDeviceProcAddr>("vkGetDeviceProcAddr"));

		_functions = VulkanDeviceFunctions(this);

		//get all queues
		for (auto& info : queueCreateInfo) {
			VkDeviceQueueInfo2 getInfo = {};
			getInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
			getInfo.queueFamilyIndex = info.queueFamilyIndex;

			for (uint32_t i = 0; i < info.queueCount; ++i) {
				getInfo.queueIndex = i;

				VkQueue queue = {};
				_functions.vkGetDeviceQueue(info.queueFamilyIndex, i, &queue);

				_queues.push_back(VulkanQueue{ getInfo.queueFamilyIndex, i, queue });
			}
		}
	}

	template<typename FunctionPtr, typename = std::enable_if_t<std::is_function_v<std::remove_pointer_t<FunctionPtr>>>>
	auto getProcAddr(const char* name) const {
		return reinterpret_cast<FunctionPtr>(_getDeviceProcAddr(_device, name));
	}

	VkDevice getDevice() const;

	const VulkanDeviceFunctions& functions() const;

	const std::vector<VulkanQueue>& queues() const {
		return _queues;
	}
private:
	std::vector<VulkanQueue> _queues;
	VulkanDeviceFunctions _functions;
	PFN_vkGetDeviceProcAddr _getDeviceProcAddr = nullptr;
	VulkanPhysicalDevice _physicalDevice;
	VkDevice _device = {};
};
