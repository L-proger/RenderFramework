#define VK_INSTANCE_FUNCTIONS \
    VK_USE_INSTANCE_FUNCTION(vkDestroyInstance) \
    VK_USE_INSTANCE_FUNCTION(vkEnumeratePhysicalDevices) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFeatures) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFormatProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceImageFormatProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceMemoryProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetInstanceProcAddr) \
    VK_USE_INSTANCE_FUNCTION(vkGetDeviceProcAddr) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDevice) \
    VK_USE_INSTANCE_FUNCTION(vkEnumerateDeviceExtensionProperties) \
    VK_USE_INSTANCE_FUNCTION(vkEnumerateDeviceLayerProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSparseImageFormatProperties) \
    VK_USE_INSTANCE_FUNCTION(vkEnumeratePhysicalDeviceGroups) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFeatures2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceProperties2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFormatProperties2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceImageFormatProperties2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceMemoryProperties2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSparseImageFormatProperties2) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalBufferProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalFenceProperties) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalSemaphoreProperties) \
    VK_USE_INSTANCE_FUNCTION(vkDestroySurfaceKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDevicePresentRectanglesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPropertiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlanePropertiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetDisplayPlaneSupportedDisplaysKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetDisplayModePropertiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDisplayModeKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilitiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDisplayPlaneSurfaceKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFeatures2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceFormatProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceImageFormatProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceMemoryProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSparseImageFormatProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkEnumeratePhysicalDeviceGroupsKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalBufferPropertiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalFencePropertiesKHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilities2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceFormats2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceDisplayPlaneProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetDisplayModeProperties2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkGetDisplayPlaneCapabilities2KHR) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDebugReportCallbackEXT) \
    VK_USE_INSTANCE_FUNCTION(vkDestroyDebugReportCallbackEXT) \
    VK_USE_INSTANCE_FUNCTION(vkDebugReportMessageEXT) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceExternalImageFormatPropertiesNV) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX) \
    VK_USE_INSTANCE_FUNCTION(vkReleaseDisplayEXT) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilities2EXT) \
    VK_USE_INSTANCE_FUNCTION(vkCreateDebugUtilsMessengerEXT) \
    VK_USE_INSTANCE_FUNCTION(vkDestroyDebugUtilsMessengerEXT) \
    VK_USE_INSTANCE_FUNCTION(vkSubmitDebugUtilsMessageEXT) \
    VK_USE_INSTANCE_FUNCTION(vkGetPhysicalDeviceMultisamplePropertiesEXT) \

#define VK_DEVICE_FUNCTIONS \
    VK_USE_DEVICE_FUNCTION(vkDestroyDevice) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceQueue) \
    VK_USE_DEVICE_FUNCTION(vkDeviceWaitIdle) \
    VK_USE_DEVICE_FUNCTION(vkAllocateMemory) \
    VK_USE_DEVICE_FUNCTION(vkFreeMemory) \
    VK_USE_DEVICE_FUNCTION(vkMapMemory) \
    VK_USE_DEVICE_FUNCTION(vkUnmapMemory) \
    VK_USE_DEVICE_FUNCTION(vkFlushMappedMemoryRanges) \
    VK_USE_DEVICE_FUNCTION(vkInvalidateMappedMemoryRanges) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceMemoryCommitment) \
    VK_USE_DEVICE_FUNCTION(vkBindBufferMemory) \
    VK_USE_DEVICE_FUNCTION(vkBindImageMemory) \
    VK_USE_DEVICE_FUNCTION(vkGetBufferMemoryRequirements) \
    VK_USE_DEVICE_FUNCTION(vkGetImageMemoryRequirements) \
    VK_USE_DEVICE_FUNCTION(vkGetImageSparseMemoryRequirements) \
    VK_USE_DEVICE_FUNCTION(vkCreateFence) \
    VK_USE_DEVICE_FUNCTION(vkDestroyFence) \
    VK_USE_DEVICE_FUNCTION(vkResetFences) \
    VK_USE_DEVICE_FUNCTION(vkGetFenceStatus) \
    VK_USE_DEVICE_FUNCTION(vkWaitForFences) \
    VK_USE_DEVICE_FUNCTION(vkCreateSemaphore) \
    VK_USE_DEVICE_FUNCTION(vkDestroySemaphore) \
    VK_USE_DEVICE_FUNCTION(vkCreateEvent) \
    VK_USE_DEVICE_FUNCTION(vkDestroyEvent) \
    VK_USE_DEVICE_FUNCTION(vkGetEventStatus) \
    VK_USE_DEVICE_FUNCTION(vkSetEvent) \
    VK_USE_DEVICE_FUNCTION(vkResetEvent) \
    VK_USE_DEVICE_FUNCTION(vkCreateQueryPool) \
    VK_USE_DEVICE_FUNCTION(vkDestroyQueryPool) \
    VK_USE_DEVICE_FUNCTION(vkGetQueryPoolResults) \
    VK_USE_DEVICE_FUNCTION(vkCreateBuffer) \
    VK_USE_DEVICE_FUNCTION(vkDestroyBuffer) \
    VK_USE_DEVICE_FUNCTION(vkCreateBufferView) \
    VK_USE_DEVICE_FUNCTION(vkDestroyBufferView) \
    VK_USE_DEVICE_FUNCTION(vkCreateImage) \
    VK_USE_DEVICE_FUNCTION(vkDestroyImage) \
    VK_USE_DEVICE_FUNCTION(vkGetImageSubresourceLayout) \
    VK_USE_DEVICE_FUNCTION(vkCreateImageView) \
    VK_USE_DEVICE_FUNCTION(vkDestroyImageView) \
    VK_USE_DEVICE_FUNCTION(vkCreateShaderModule) \
    VK_USE_DEVICE_FUNCTION(vkDestroyShaderModule) \
    VK_USE_DEVICE_FUNCTION(vkCreatePipelineCache) \
    VK_USE_DEVICE_FUNCTION(vkDestroyPipelineCache) \
    VK_USE_DEVICE_FUNCTION(vkGetPipelineCacheData) \
    VK_USE_DEVICE_FUNCTION(vkMergePipelineCaches) \
    VK_USE_DEVICE_FUNCTION(vkCreateGraphicsPipelines) \
    VK_USE_DEVICE_FUNCTION(vkCreateComputePipelines) \
    VK_USE_DEVICE_FUNCTION(vkDestroyPipeline) \
    VK_USE_DEVICE_FUNCTION(vkCreatePipelineLayout) \
    VK_USE_DEVICE_FUNCTION(vkDestroyPipelineLayout) \
    VK_USE_DEVICE_FUNCTION(vkCreateSampler) \
    VK_USE_DEVICE_FUNCTION(vkDestroySampler) \
    VK_USE_DEVICE_FUNCTION(vkCreateDescriptorSetLayout) \
    VK_USE_DEVICE_FUNCTION(vkDestroyDescriptorSetLayout) \
    VK_USE_DEVICE_FUNCTION(vkCreateDescriptorPool) \
    VK_USE_DEVICE_FUNCTION(vkDestroyDescriptorPool) \
    VK_USE_DEVICE_FUNCTION(vkResetDescriptorPool) \
    VK_USE_DEVICE_FUNCTION(vkAllocateDescriptorSets) \
    VK_USE_DEVICE_FUNCTION(vkFreeDescriptorSets) \
    VK_USE_DEVICE_FUNCTION(vkUpdateDescriptorSets) \
    VK_USE_DEVICE_FUNCTION(vkCreateFramebuffer) \
    VK_USE_DEVICE_FUNCTION(vkDestroyFramebuffer) \
    VK_USE_DEVICE_FUNCTION(vkCreateRenderPass) \
    VK_USE_DEVICE_FUNCTION(vkDestroyRenderPass) \
    VK_USE_DEVICE_FUNCTION(vkGetRenderAreaGranularity) \
    VK_USE_DEVICE_FUNCTION(vkCreateCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkDestroyCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkResetCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkAllocateCommandBuffers) \
    VK_USE_DEVICE_FUNCTION(vkFreeCommandBuffers) \
    VK_USE_DEVICE_FUNCTION(vkBindBufferMemory2) \
    VK_USE_DEVICE_FUNCTION(vkBindImageMemory2) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceGroupPeerMemoryFeatures) \
    VK_USE_DEVICE_FUNCTION(vkGetImageMemoryRequirements2) \
    VK_USE_DEVICE_FUNCTION(vkGetBufferMemoryRequirements2) \
    VK_USE_DEVICE_FUNCTION(vkGetImageSparseMemoryRequirements2) \
    VK_USE_DEVICE_FUNCTION(vkTrimCommandPool) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceQueue2) \
    VK_USE_DEVICE_FUNCTION(vkCreateSamplerYcbcrConversion) \
    VK_USE_DEVICE_FUNCTION(vkDestroySamplerYcbcrConversion) \
    VK_USE_DEVICE_FUNCTION(vkCreateDescriptorUpdateTemplate) \
    VK_USE_DEVICE_FUNCTION(vkDestroyDescriptorUpdateTemplate) \
    VK_USE_DEVICE_FUNCTION(vkUpdateDescriptorSetWithTemplate) \
    VK_USE_DEVICE_FUNCTION(vkGetDescriptorSetLayoutSupport) \
    VK_USE_DEVICE_FUNCTION(vkCreateSwapchainKHR) \
    VK_USE_DEVICE_FUNCTION(vkDestroySwapchainKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetSwapchainImagesKHR) \
    VK_USE_DEVICE_FUNCTION(vkAcquireNextImageKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceGroupPresentCapabilitiesKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceGroupSurfacePresentModesKHR) \
    VK_USE_DEVICE_FUNCTION(vkAcquireNextImage2KHR) \
    VK_USE_DEVICE_FUNCTION(vkCreateSharedSwapchainsKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetDeviceGroupPeerMemoryFeaturesKHR) \
    VK_USE_DEVICE_FUNCTION(vkTrimCommandPoolKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetMemoryFdKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetMemoryFdPropertiesKHR) \
    VK_USE_DEVICE_FUNCTION(vkImportSemaphoreFdKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetSemaphoreFdKHR) \
    VK_USE_DEVICE_FUNCTION(vkCreateDescriptorUpdateTemplateKHR) \
    VK_USE_DEVICE_FUNCTION(vkDestroyDescriptorUpdateTemplateKHR) \
    VK_USE_DEVICE_FUNCTION(vkUpdateDescriptorSetWithTemplateKHR) \
    VK_USE_DEVICE_FUNCTION(vkCreateRenderPass2KHR) \
    VK_USE_DEVICE_FUNCTION(vkGetSwapchainStatusKHR) \
    VK_USE_DEVICE_FUNCTION(vkImportFenceFdKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetFenceFdKHR) \
    VK_USE_DEVICE_FUNCTION(vkGetImageMemoryRequirements2KHR) \
    VK_USE_DEVICE_FUNCTION(vkGetBufferMemoryRequirements2KHR) \
    VK_USE_DEVICE_FUNCTION(vkGetImageSparseMemoryRequirements2KHR) \
    VK_USE_DEVICE_FUNCTION(vkCreateSamplerYcbcrConversionKHR) \
    VK_USE_DEVICE_FUNCTION(vkDestroySamplerYcbcrConversionKHR) \
    VK_USE_DEVICE_FUNCTION(vkBindBufferMemory2KHR) \
    VK_USE_DEVICE_FUNCTION(vkBindImageMemory2KHR) \
    VK_USE_DEVICE_FUNCTION(vkGetDescriptorSetLayoutSupportKHR) \
    VK_USE_DEVICE_FUNCTION(vkDebugMarkerSetObjectTagEXT) \
    VK_USE_DEVICE_FUNCTION(vkDebugMarkerSetObjectNameEXT) \
    VK_USE_DEVICE_FUNCTION(vkGetShaderInfoAMD) \
    VK_USE_DEVICE_FUNCTION(vkCreateIndirectCommandsLayoutNVX) \
    VK_USE_DEVICE_FUNCTION(vkDestroyIndirectCommandsLayoutNVX) \
    VK_USE_DEVICE_FUNCTION(vkCreateObjectTableNVX) \
    VK_USE_DEVICE_FUNCTION(vkDestroyObjectTableNVX) \
    VK_USE_DEVICE_FUNCTION(vkRegisterObjectsNVX) \
    VK_USE_DEVICE_FUNCTION(vkUnregisterObjectsNVX) \
    VK_USE_DEVICE_FUNCTION(vkDisplayPowerControlEXT) \
    VK_USE_DEVICE_FUNCTION(vkRegisterDeviceEventEXT) \
    VK_USE_DEVICE_FUNCTION(vkRegisterDisplayEventEXT) \
    VK_USE_DEVICE_FUNCTION(vkGetSwapchainCounterEXT) \
    VK_USE_DEVICE_FUNCTION(vkGetRefreshCycleDurationGOOGLE) \
    VK_USE_DEVICE_FUNCTION(vkGetPastPresentationTimingGOOGLE) \
    VK_USE_DEVICE_FUNCTION(vkSetHdrMetadataEXT) \
    VK_USE_DEVICE_FUNCTION(vkSetDebugUtilsObjectNameEXT) \
    VK_USE_DEVICE_FUNCTION(vkSetDebugUtilsObjectTagEXT) \
    VK_USE_DEVICE_FUNCTION(vkCreateValidationCacheEXT) \
    VK_USE_DEVICE_FUNCTION(vkDestroyValidationCacheEXT) \
    VK_USE_DEVICE_FUNCTION(vkMergeValidationCachesEXT) \
    VK_USE_DEVICE_FUNCTION(vkGetValidationCacheDataEXT) \
    VK_USE_DEVICE_FUNCTION(vkGetMemoryHostPointerPropertiesEXT) \

#define VK_DEVICE_QUEUE_FUNCTIONS \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueueSubmit) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueueWaitIdle) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueueBindSparse) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueuePresentKHR) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueueBeginDebugUtilsLabelEXT) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueueEndDebugUtilsLabelEXT) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkQueueInsertDebugUtilsLabelEXT) \
    VK_USE_DEVICE_QUEUE_FUNCTION(vkGetQueueCheckpointDataNV) \

#define VK_DEVICE_CMD_FUNCTIONS \
    VK_USE_DEVICE_CMD_FUNCTION(vkBeginCommandBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkEndCommandBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkResetCommandBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBindPipeline) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetViewport) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetScissor) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetLineWidth) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetDepthBias) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetBlendConstants) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetDepthBounds) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetStencilCompareMask) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetStencilWriteMask) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetStencilReference) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBindDescriptorSets) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBindIndexBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBindVertexBuffers) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDraw) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndexed) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndirect) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndexedIndirect) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDispatch) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDispatchIndirect) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdCopyBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdCopyImage) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBlitImage) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdCopyBufferToImage) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdCopyImageToBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdUpdateBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdFillBuffer) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdClearColorImage) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdClearDepthStencilImage) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdClearAttachments) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdResolveImage) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetEvent) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdResetEvent) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdWaitEvents) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdPipelineBarrier) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBeginQuery) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdEndQuery) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdResetQueryPool) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdWriteTimestamp) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdCopyQueryPoolResults) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdPushConstants) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBeginRenderPass) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdNextSubpass) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdEndRenderPass) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdExecuteCommands) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetDeviceMask) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDispatchBase) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetDeviceMaskKHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDispatchBaseKHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdPushDescriptorSetKHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdPushDescriptorSetWithTemplateKHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBeginRenderPass2KHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdNextSubpass2KHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdEndRenderPass2KHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndirectCountKHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndexedIndirectCountKHR) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDebugMarkerBeginEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDebugMarkerEndEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDebugMarkerInsertEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndirectCountAMD) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdDrawIndexedIndirectCountAMD) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBeginConditionalRenderingEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdEndConditionalRenderingEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdProcessCommandsNVX) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdReserveSpaceForCommandsNVX) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetViewportWScalingNV) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetDiscardRectangleEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdBeginDebugUtilsLabelEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdEndDebugUtilsLabelEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdInsertDebugUtilsLabelEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetSampleLocationsEXT) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdWriteBufferMarkerAMD) \
    VK_USE_DEVICE_CMD_FUNCTION(vkCmdSetCheckpointNV) \

#define VK_GLOBAL_FUNCTIONS \
    VK_USE_GLOBAL_FUNCTION(vkCreateInstance) \
    VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceExtensionProperties) \
    VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceLayerProperties) \
    VK_USE_GLOBAL_FUNCTION(vkEnumerateInstanceVersion) \