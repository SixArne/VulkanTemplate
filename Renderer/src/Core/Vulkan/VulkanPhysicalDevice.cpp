#include "VulkanPhysicalDevice.h"
#include "VulkanApplication.h"

#include "src/Core/Logger/Logger.h"
#include "VulkanSurface.h"

#include <stdexcept>
#include <vector>
#include <set>
#include <GLFW/glfw3.h>

#include "Helpers/Helpers.h"

Core::Vulkan::VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanApplication* vulkanApplication)
    : m_VulkanApp{vulkanApplication}
{
    PickPhysicalDevice();
}

Core::Vulkan::VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

void Core::Vulkan::VulkanPhysicalDevice::PickPhysicalDevice()
{
    VkInstance instance = m_VulkanApp->GetInstance();

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        L_ERROR("Failed to find GPUs with Vulkan support");
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // TODO: add device rating
    for (const auto& device : devices)
    {
        uint32_t score = RatePhysicalDevice(device);
        m_PhysicalDevices.insert({score, device});
    }

    if (m_PhysicalDevices.rbegin()->first > 0)
    {
        m_PhysicalDevice = m_PhysicalDevices.rbegin()->second;

        vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_DeviceProperties);

        L_DEBUG("Choose: {}", m_DeviceProperties.deviceName);
    }
    else
    {
        L_ERROR("Failed to find a suitable GPU");
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    L_DEBUG("Vulkan Physical device chosen")
}

uint32_t Core::Vulkan::VulkanPhysicalDevice::RatePhysicalDevice(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties{};
    VkPhysicalDeviceFeatures deviceFeatures{};

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    uint32_t currentScore{};

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        currentScore += 1000;
    }

    currentScore += deviceProperties.limits.maxImageDimension2D;

    // Requirements
    if (!deviceFeatures.geometryShader)
    {
        return 0;
    }

    if (!deviceFeatures.tessellationShader)
    {
        return 0;
    }

    if (!IsDeviceSuitable(device))
    {
        return 0;
    }

    return currentScore;
}

bool Core::Vulkan::VulkanPhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    Helpers::QueueFamilyIndices indices = Helpers::FindQueueFamilies(device, m_VulkanApp->GetSurface());

    bool extensionsSupported = CheckDeviceExtensionsSupport(device);

    bool swapChainAdequate{false};
    if (extensionsSupported)
    {
        Helpers::SwapChainSupportDetails swapChainSupport = Helpers::QuerySwapChainSupport(device, m_VulkanApp->GetSurface());
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.IsComplete() && extensionsSupported && swapChainAdequate;
}

bool Core::Vulkan::VulkanPhysicalDevice::CheckDeviceExtensionsSupport(VkPhysicalDevice device)
{
    const auto& deviceExtensions = m_VulkanApp->DeviceExtensions;

    uint32_t extensionCount{};
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension: availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}