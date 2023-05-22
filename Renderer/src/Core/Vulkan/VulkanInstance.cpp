#include "VulkanInstance.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>

Core::Vulkan::VulkanInstance::VulkanInstance()
{
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

    uint32_t glfwExtensionCount{ 0 };
    const char** glfwExtensions{ glfwGetRequiredInstanceExtensions(&glfwExtensionCount) };

    instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
    instanceCreateInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    uint32_t extensionCount{ 0 };
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "Available extensions:" << std::endl;
    for (const auto& extension : extensions)
    {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
}