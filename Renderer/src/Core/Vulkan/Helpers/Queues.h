#ifndef VULKAN_RENDERER_QUEUE_HELPERS
#define VULKAN_RENDERER_QUEUE_HELPERS

#include <optional>
#include <GLFW/glfw3.h>

namespace Core::Vulkan::Helpers
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    inline QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices{};

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily: queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }

            if (indices.IsComplete())
            {
                break;
            }

            i++;
        }

        return indices;
    }
}

#endif // VULKAN_RENDERER_QUEUE_HELPERS
