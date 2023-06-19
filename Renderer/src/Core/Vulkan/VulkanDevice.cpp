#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanValidation.h"
#include "VulkanApplication.h"

#include "Helpers/Helpers.h"
#include "src/Core/Logger/Logger.h"
#include "src/Core/Errors/VulkanErrors.h"

#include <set>

namespace Core::Vulkan
{
    VulkanDevice::VulkanDevice(const VulkanApplication* vulkanApplication)
    :m_VulkanApp{vulkanApplication}
    {
        CreateDevice();
    }

    VulkanDevice::~VulkanDevice()
    {
        vkDestroyDevice(m_Device, nullptr);
    }

    void VulkanDevice::CreateDevice()
    {
        Helpers::QueueFamilyIndices indices = Helpers::FindQueueFamilies(m_VulkanApp->GetPhysicalDevice(), m_VulkanApp->GetSurface());

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
        
        float queuePriority = 1.0f;

        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;

            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(m_VulkanApp->DeviceExtensions.size());
        createInfo.ppEnabledExtensionNames = m_VulkanApp->DeviceExtensions.data();

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

        vkGetDeviceQueue(m_Device, indices.presentFamily.value(), 0, &m_PresentQueue);
        vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);

        L_DEBUG("Vulkan Logical device created")
    }
}

