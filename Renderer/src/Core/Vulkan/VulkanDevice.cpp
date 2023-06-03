#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanValidation.h"
#include "VulkanApplication.h"

#include "Helpers/Queues.h"
#include "src/Core/Logger/Logger.h"
#include "src/Core/Errors/VulkanErrors.h"

Core::Vulkan::VulkanDevice::VulkanDevice(const VulkanApplication* vulkanApplication)
    :m_VulkanApp{vulkanApplication}
{
    CreateDevice();
}

Core::Vulkan::VulkanDevice::~VulkanDevice()
{
    vkDestroyDevice(m_Device, nullptr);
}

void Core::Vulkan::VulkanDevice::CreateDevice()
{
    Helpers::QueueFamilyIndices indices = Helpers::FindQueueFamilies(m_VulkanApp->GetPhysicalDevice());

    // Graphics queue
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if (m_VulkanApp->GetValidation()->AreValidationLayersEnabled())
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanValidation::ValidationLayers.size());
        createInfo.ppEnabledLayerNames = VulkanValidation::ValidationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_VulkanApp->GetPhysicalDevice(), &createInfo, nullptr, &m_Device) != VK_SUCCESS)
    {
        L_ERROR("FAILED TO CREATE LOGICAL DEVICE");
        throw Errors::vulkan_device_exception("Failed to create device");
    }
}