#ifndef VULKAN_RENDERER_VULKANAPPLICATION_H
#define VULKAN_RENDERER_VULKANAPPLICATION_H

#include <GLFW/glfw3.h>

namespace Core::Vulkan
{
    class VulkanInstance;
    class VulkanValidation;
    class VulkanPhysicalDevice;
    class VulkanDevice;

    class VulkanApplication final
    {
    public:
        VulkanApplication();
        ~VulkanApplication();

        void Init();

        // Rule of 5
        VulkanApplication(const VulkanApplication&) = delete;
        VulkanApplication& operator=(const VulkanApplication&) = delete;
        VulkanApplication(VulkanApplication&&) = default;
        VulkanApplication& operator=(VulkanApplication&&) = default;

        const VkPhysicalDevice GetPhysicalDevice() const;
        const VkInstance GetInstance() const;
        const VulkanValidation* GetValidation() const;
        const VkDevice GetDevice() const;

    private:
        VulkanInstance* m_VulkanInstance;
        VulkanValidation* m_VulkanValidation;
        VulkanPhysicalDevice* m_VulkanPhysicalDevice;
        VulkanDevice* m_VulkanDevice;
    };
}

#endif //VULKAN_RENDERER_VULKANAPPLICATION_H
