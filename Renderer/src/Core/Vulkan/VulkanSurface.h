#ifndef VULKAN_RENDERER_VULKANSURFACE_H
#define VULKAN_RENDERER_VULKANSURFACE_H

#include <GLFW/glfw3.h>

namespace Core::Vulkan
{
    class VulkanApplication;

    class VulkanSurface final
    {
    public:
        VulkanSurface(const VulkanApplication* app);
        ~VulkanSurface();

        const VkSurfaceKHR GetSurface() const { return m_Surface; };


    private:
        void Init();

        VkSurfaceKHR m_Surface{};
        const VulkanApplication* m_App{};
    };
}

#endif
