#ifndef VULKAN_RENDERER_PHYSICAL_DEVICE_H
#define VULKAN_RENDERER_PHYSICAL_DEVICE_H

#include <GLFW/glfw3.h>
#include <map>

namespace Core::Vulkan
{
    ///////////////////////////////////////////////////////////////////////////
    // VulkanPhysicalDevice
    // - This gets destroyed by the VkInstance.
    ///////////////////////////////////////////////////////////////////////////
    class VulkanPhysicalDevice
    {
    public:
        VulkanPhysicalDevice(VkInstance instance);
        ~VulkanPhysicalDevice();

        //void PickPhysicalDevice(VkInstance instance) {};

        // Rule of 5
        VulkanPhysicalDevice(const VulkanPhysicalDevice&) = delete;
        VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice&) = delete;
        VulkanPhysicalDevice(VulkanPhysicalDevice&&) = default;
        VulkanPhysicalDevice& operator=(VulkanPhysicalDevice&&) = default;

    private:
        void PickPhysicalDevice();

        // TODO: Make this function check for more.
        uint32_t RatePhysicalDevice(VkPhysicalDevice device);

        std::multimap<uint32_t, VkPhysicalDevice> m_PhysicalDevices{};

        VkPhysicalDevice m_PhysicalDevice{VK_NULL_HANDLE};
        VkPhysicalDeviceProperties m_DeviceProperties{};

        VkInstance m_VkInstance{};
    };
}

#endif //VULKAN_RENDERER_PHYSICAL_DEVICE_H
