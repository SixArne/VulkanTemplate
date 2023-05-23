#include "VulkanInstance.h"
#include "VulkanValidation.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>


Core::Vulkan::VulkanInstance::VulkanInstance()
{
    #ifdef DEBUG
    {
        m_EnableValidationLayers = true;
    }
    #endif // DEBUG

    if (m_EnableValidationLayers)
    {
        spdlog::info("Validation layers enabled!");
    }
    else
    {
        spdlog::info("Validation layers disabled!");
    }

    CreateInstance();
}

Core::Vulkan::VulkanInstance::~VulkanInstance()
{
    vkDestroyInstance(m_Instance, nullptr);
    spdlog::info("VulkanInstance::Destroy()");
}

void Core::Vulkan::VulkanInstance::CreateInstance()
{
    spdlog::info("VulkanInstance::Init()");

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
