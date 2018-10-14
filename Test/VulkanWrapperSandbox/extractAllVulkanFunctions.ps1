$text = Get-Content "C:\VulkanSDK\1.1.82.1\Include\vulkan\vulkan_core.h" -Raw 

#Write-Host $text

$AllMatches = [regex]::matches($text, 'typedef\s+([^\s]+)\s+\(\s*VKAPI_PTR\s+\*([^\)]+)\)\s*\(([^\)]+)\)')

Write-Host "!!!!!!!!!!!!!!!!"


$DeviceFunctions = New-Object System.Collections.ArrayList
$DeviceCmdFunctions = New-Object System.Collections.ArrayList
$DeviceQueueFunctions = New-Object System.Collections.ArrayList
$InstanceFunctions = New-Object System.Collections.ArrayList

$UnknownFunctions = New-Object System.Collections.ArrayList

ForEach ($match in $AllMatches) {
    [string]$retval = $match.Groups[1].Value
    [string]$name = $match.Groups[2].Value
    [string]$params = $match.Groups[3].Value

    #Device instance functions
    if($params.StartsWith("VkDevice ") -and ($name -ne 'PFN_vkGetDeviceProcAddr')){
        $DeviceFunctions.Add($match) | Out-Null;
    }elseif($params.StartsWith("VkCommandBuffer ")){
        $DeviceCmdFunctions.Add($match) | Out-Null;
    }elseif($params.StartsWith("VkQueue ")){
        $DeviceQueueFunctions.Add($match) | Out-Null;
    }elseif($params.StartsWith("VkInstance ") -or $params.StartsWith("VkPhysicalDevice ") -or ($name -eq 'PFN_vkGetDeviceProcAddr')){
        $InstanceFunctions.Add($match) | Out-Null;
    }elseif(!$name.EndsWith("CallbackEXT") -and !$name.EndsWith("Function") -and !$name.EndsWith("Notification")){
        $UnknownFunctions.Add($match) | Out-Null;
    }
}


function generateFunctionsGroup($functions, [string]$groupName, [string]$wrapName){
    Write-Host "#define $groupName \"
    ForEach ($function in $functions) {
        $define = "    $wrapName(" + $function.Groups[2].Value.Replace("PFN_", "") + ') \'
        Write-Host $define
    }
    Write-Host ""
}
generateFunctionsGroup $InstanceFunctions "VK_INSTANCE_FUNCTIONS" "VK_USE_INSTANCE_FUNCTION"
generateFunctionsGroup $DeviceFunctions "VK_DEVICE_FUNCTIONS" "VK_USE_DEVICE_FUNCTION"
generateFunctionsGroup $DeviceQueueFunctions "VK_DEVICE_QUEUE_FUNCTIONS" "VK_USE_DEVICE_QUEUE_FUNCTION"
generateFunctionsGroup $DeviceCmdFunctions "VK_DEVICE_CMD_FUNCTIONS" "VK_USE_DEVICE_CMD_FUNCTION"

generateFunctionsGroup $UnknownFunctions "VK_GLOBAL_FUNCTIONS" "VK_USE_GLOBAL_FUNCTION"