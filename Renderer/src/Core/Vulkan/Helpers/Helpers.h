#ifndef VULKAN_RENDERER_QUEUE_HELPERS
#define VULKAN_RENDERER_QUEUE_HELPERS

#include <optional>
#include <vector>
#include <GLFW/glfw3.h>

namespace Core::Vulkan::Helpers
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value()
                && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities{};
        std::vector<VkSurfaceFormatKHR> formats{};
        std::vector<VkPresentModeKHR> presentModes{};
    };

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    VkImageView CreateImageView(VkDevice device, VkImage image, VkFormat format);
}

#endif // VULKAN_RENDERER_QUEUE_HELPERS
