#ifndef VULKAN_RENDERER_VULKAN_DEVICE_H
#define VULKAN_RENDERER_VULKAN_DEVICE_H

#include <GLFW/glfw3.h>

namespace Core::Vulkan
{
    class VulkanApplication;

    class VulkanDevice final
    {
    public:
        VulkanDevice(const VulkanApplication* vulkanApplication);
        ~VulkanDevice();

        // Rule of 5
        VulkanDevice(const VulkanDevice&) = delete;
        VulkanDevice& operator=(const VulkanDevice&) = delete;
        VulkanDevice(VulkanDevice&&) = default;
        VulkanDevice& operator=(VulkanDevice&&) = default;

        void CreateDevice();
        const VkDevice GetDevice() const { return m_Device; };

    private:
        VkDevice m_Device{};

        const VulkanApplication* m_VulkanApp{};
    };
}

#endif //VULKAN_RENDERER_VULKAN_DEVICE_H