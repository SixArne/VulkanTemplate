#ifndef VULKAN_RENDERER_VULKANAPPLICATION_H
#define VULKAN_RENDERER_VULKANAPPLICATION_H

namespace Core::Vulkan
{
    class VulkanInstance;

    class VulkanApplication
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

    private:
        VulkanInstance* m_VulkanInstance;
    };
}

#endif //VULKAN_RENDERER_VULKANAPPLICATION_H