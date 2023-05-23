#include "VulkanPhysicalDevice.h"

#include "src/Core/Logger/Logger.h"
#include <stdexcept>
#include <vector>
#include <GLFW/glfw3.h>

Core::Vulkan::VulkanPhysicalDevice::VulkanPhysicalDevice(VkInstance instance)
    : m_VkInstance(instance)
{
    PickPhysicalDevice();
}

Core::Vulkan::VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

void Core::Vulkan::VulkanPhysicalDevice::PickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, devices.data());

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
        throw std::runtime_error("failed to find a suitable GPU!");
    }
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

    return currentScore;
}