#ifndef VULKAN_RENDERER_VULKANAPPLICATION_H
#define VULKAN_RENDERER_VULKANAPPLICATION_H

#include <GLFW/glfw3.h>

namespace Core
{
    class Window;
}

namespace Core::Vulkan
{
    class VulkanInstance;
    class VulkanValidation;
    class VulkanPhysicalDevice;
    class VulkanDevice;
    class VulkanSurface;

    class VulkanApplication final
    {
    public:
        VulkanApplication();
        VulkanApplication(const Window* window);
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
        const VkSurfaceKHR GetSurface() const;

        const Window* GetWindow() const;

    private:
        VulkanInstance* m_VulkanInstance{};
        VulkanValidation* m_VulkanValidation{};
        VulkanPhysicalDevice* m_VulkanPhysicalDevice{};
        VulkanDevice* m_VulkanDevice{};
        VulkanSurface* m_VulkanSurface{};

        const Window* m_Window{};
    };
}

#endif //VULKAN_RENDERER_VULKANAPPLICATION_H
