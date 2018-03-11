#pragma once

#define VK_GLOBAL_FUNCTIONS \
	VK_USE_GLOBAL_FUNCTION(vkCreateInstance) \
	VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceExtensionProperties) \
	VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceLayerProperties)

#define VK_INSTANCE_FUNCTIONS \
	VK_USE_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices) \
	VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFeatures) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDevice) \
    VK_USE_INSTANCE_FUNCTION(vkGetDeviceProcAddr) \
    VK_USE_INSTANCE_FUNCTION(vkDestroyInstance) \
    VK_USE_INSTANCE_FUNCTION(vkEnumerateDeviceExtensionProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkDestroySurfaceKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceMemoryProperties)

//    VK_USE_INSTANCE_FUNCTION(vkCreateWin32SurfaceKHR) \

#define VK_DEVICE_FUNCTIONS \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceQueue) \
    VK_USE_DEVICE_FUNCTION(vkDeviceWaitIdle)  \
    VK_USE_DEVICE_FUNCTION(vkDestroyDevice) \
    VK_USE_DEVICE_FUNCTION(vkCreateSemaphore) \
    VK_USE_DEVICE_FUNCTION(vkCreateCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkAllocateCommandBuffers) \
    VK_USE_DEVICE_FUNCTION(vkBeginCommandBuffer) \
    VK_USE_DEVICE_FUNCTION(vkCmdPipelineBarrier) \
    VK_USE_DEVICE_FUNCTION(vkCmdClearColorImage) \
    VK_USE_DEVICE_FUNCTION(vkEndCommandBuffer) \
    VK_USE_DEVICE_FUNCTION(vkQueueSubmit) \
    VK_USE_DEVICE_FUNCTION(vkFreeCommandBuffers) \
    VK_USE_DEVICE_FUNCTION(vkDestroyCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkDestroySemaphore) \
     \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateSwapchainKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkGetSwapchainImagesKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkAcquireNextImageKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkQueuePresentKHR) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroySwapchainKHR) \
     \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateImageView) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateFramebuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateShaderModule) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreatePipelineLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateGraphicsPipelines) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBeginRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBindPipeline) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdDraw) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdEndRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyShaderModule) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyPipelineLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyPipeline) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyRenderPass) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyFramebuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyImageView) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateFence) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateBuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkGetBufferMemoryRequirements) \
    VK_DEVICE_LEVEL_FUNCTION(vkAllocateMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkBindBufferMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkMapMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkFlushMappedMemoryRanges) \
    VK_DEVICE_LEVEL_FUNCTION(vkUnmapMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdSetViewport) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdSetScissor) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBindVertexBuffers) \
    VK_DEVICE_LEVEL_FUNCTION(vkWaitForFences) \
    VK_DEVICE_LEVEL_FUNCTION(vkResetFences) \
    VK_DEVICE_LEVEL_FUNCTION(vkFreeMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyBuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyFence) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdCopyBuffer) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateImage) \
    VK_DEVICE_LEVEL_FUNCTION(vkGetImageMemoryRequirements) \
    VK_DEVICE_LEVEL_FUNCTION(vkBindImageMemory) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateSampler) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdCopyBufferToImage) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateDescriptorSetLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkCreateDescriptorPool) \
    VK_DEVICE_LEVEL_FUNCTION(vkAllocateDescriptorSets) \
    VK_DEVICE_LEVEL_FUNCTION(vkUpdateDescriptorSets) \
    VK_DEVICE_LEVEL_FUNCTION(vkCmdBindDescriptorSets) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyDescriptorPool) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyDescriptorSetLayout) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroySampler) \
    VK_DEVICE_LEVEL_FUNCTION(vkDestroyImage)