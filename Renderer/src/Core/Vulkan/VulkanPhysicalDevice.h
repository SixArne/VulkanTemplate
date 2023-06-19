#ifndef VULKAN_RENDERER_PHYSICAL_DEVICE_H
#define VULKAN_RENDERER_PHYSICAL_DEVICE_H

#include <GLFW/glfw3.h>
#include <map>

namespace Core::Vulkan
{
    class VulkanApplication;
    ///////////////////////////////////////////////////////////////////////////
    // VulkanPhysicalDevice
    // - This gets destroyed by the VkInstance.
    ///////////////////////////////////////////////////////////////////////////
    class VulkanPhysicalDevice final
    {
    public:
        VulkanPhysicalDevice(const VulkanApplication* vulkanApp);
        ~VulkanPhysicalDevice();

        //void PickPhysicalDevice(VkInstance instance) {};

        // Rule of 5
        VulkanPhysicalDevice(const VulkanPhysicalDevice&) = delete;
        VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice&) = delete;
        VulkanPhysicalDevice(VulkanPhysicalDevice&&) = default;
        VulkanPhysicalDevice& operator=(VulkanPhysicalDevice&&) = default;

        const VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }

    private:
        void PickPhysicalDevice();
        bool IsDeviceSuitable(VkPhysicalDevice device);
        bool CheckDeviceExtensionsSupport(VkPhysicalDevice device);

        // TODO: Make this function check for more.
        uint32_t RatePhysicalDevice(VkPhysicalDevice device);

        std::multimap<uint32_t, VkPhysicalDevice> m_PhysicalDevices{};

        VkPhysicalDevice m_PhysicalDevice{VK_NULL_HANDLE};
        VkPhysicalDeviceProperties m_DeviceProperties{};

        const VulkanApplication* m_VulkanApp{};
    };
}

#endif //VULKAN_RENDERER_PHYSICAL_DEVICE_H
