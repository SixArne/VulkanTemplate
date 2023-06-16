#include "VulkanInstance.h"
#include "VulkanValidation.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include "src/Core/Logger/Logger.h"


Core::Vulkan::VulkanInstance::VulkanInstance()
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

    CreateInstance();
}

Core::Vulkan::VulkanInstance::~VulkanInstance()
{
    vkDestroyInstance(m_Instance, nullptr);
    L_DEBUG("Validation Instance destroyed");
}

void Core::Vulkan::VulkanInstance::CreateInstance()
{
    // Check if validation layers are available


    ///////////////////////////////////////////////////////////
    // Create Vulkan instance
    ///////////////////////////////////////////////////////////
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Renderer";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Vulkan Renderer";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;

    auto extensions = GetRequiredExtensions();
    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

    ///////////////////////////////////////////////////////////
    // Validation layers
    ///////////////////////////////////////////////////////////
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (m_EnableValidationLayers)
    {
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(VulkanValidation::ValidationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = VulkanValidation::ValidationLayers.data();

        VulkanValidation::PopulateDebugMessengerCreateInfo(debugCreateInfo);
        instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else
    {
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.pNext = nullptr;
    }

    ///////////////////////////////////////////////////////////
    // Create Vulkan instance
    ///////////////////////////////////////////////////////////
    if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS)
    {
        L_ERROR("Failed to create Vulkan Instance");
        throw std::runtime_error("Failed to create instance!");
    }

    ///////////////////////////////////////////////////////////
    // Print available extensions
    ///////////////////////////////////////////////////////////
    std::cout << "Available extensions:" << std::endl;
    for (const auto& extension : extensions)
    {
        std::cout << "\t" << extension << std::endl;
    }

    L_DEBUG("Vulkan Instance created");
}

std::vector<const char*> Core::Vulkan::VulkanInstance::GetRequiredExtensions()
{
    uint32_t glfwExtensionCount{ 0 };
    const char** glfwExtensions{ glfwGetRequiredInstanceExtensions(&glfwExtensionCount) };

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (m_EnableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}
