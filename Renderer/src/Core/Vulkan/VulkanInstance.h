#ifndef VULKAN_RENDERER_VULKANINSTANCE_H
#define VULKAN_RENDERER_VULKANINSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Core::Vulkan
{
    class VulkanInstance
    {
    public:
        VulkanInstance();
        ~VulkanInstance();

        void CreateInstance();

    private:
        VkInstance m_Instance;
    };
}

#endif //VULKAN_RENDERER_VULKANINSTANCE_H
