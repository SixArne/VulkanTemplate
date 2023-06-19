#include "VulkanValidation.h"
#include "VulkanApplication.h"

#include "src/Core/Logger/Logger.h"

namespace Core::Vulkan
{
    VulkanValidation::VulkanValidation(const VulkanApplication* vulkanApp)
    : m_VulkanApp{vulkanApp}
    {
        #ifdef DEBUG
        {
            m_EnableValidationLayers = true;
        }
        #endif // DEBUG

        if (m_EnableValidationLayers)
        {
            L_DEBUG("Validation layers enabled");
            
        }
        else
        {
            L_DEBUG("Validation layers disabled");
        }

        if (m_EnableValidationLayers && !CheckValidationLayerSupport())
        {
            L_ERROR("Validation layers requested, but not available!");
            throw std::runtime_error("Validation layers requested, but not available!");
        }

        // Create messenger
        CreateDebugMessenger();
    }

    VulkanValidation::~VulkanValidation()
    {
        if (m_EnableValidationLayers)
        {
            DestroyDebugUtilsMessengerEXT(m_VulkanApp->GetInstance(), m_DebugMessenger, nullptr);
            L_DEBUG("Vulkan Validation Destroyed");
        }
    }

    bool VulkanValidation::CheckValidationLayerSupport()
    {
        uint32_t layerCount{ 0 };
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (auto layerName: ValidationLayers)
        {
            bool layerFound{ false };

            for (const auto& layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
    }

    void VulkanValidation::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        createInfo.pfnUserCallback = DebugCallback;
        createInfo.pUserData = nullptr;
    }

    void VulkanValidation::CreateDebugMessenger()
    {
        if (!m_EnableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        PopulateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(m_VulkanApp->GetInstance(), &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
        {
            L_ERROR("Failed to set up debug messenger!");
            throw std::runtime_error("Failed to set up debug messenger!");
        }
        else
        {
            L_DEBUG("Vulkan Validation created");
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanValidation::DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void*
    )
    {
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        {
            L_WARN("validation layer: {}", pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
        {
            L_INFO("validation layer: {}", pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
        {
            L_DEBUG("validation layer: {}", pCallbackData->pMessage);        
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        {
            L_ERROR("validation layer: {}", pCallbackData->pMessage);        
        }
        else
        {
            L_TRACE("validation layer: {}", pCallbackData->pMessage);        
        }

        return VK_FALSE;
    }

    VkResult VulkanValidation::CreateDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger
    )
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void VulkanValidation::DestroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator
    )
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }
}
