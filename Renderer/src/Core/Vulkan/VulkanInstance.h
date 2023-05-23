#ifndef VULKAN_RENDERER_VULKANINSTANCE_H
#define VULKAN_RENDERER_VULKANINSTANCE_H

#include <GLFW/glfw3.h>
#include <vector>

namespace Core::Vulkan
{
    class VulkanInstance
    {
    public:
        VulkanInstance();
        ~VulkanInstance();

        void CreateInstance();
        const VkInstance GetInstance() const { return m_Instance; };

    private:
        std::vector<const char*> GetRequiredExtensions();
        bool m_EnableValidationLayers{false};
        VkInstance m_Instance{};
    };
}

#endif //VULKAN_RENDERER_VULKANINSTANCE_H
