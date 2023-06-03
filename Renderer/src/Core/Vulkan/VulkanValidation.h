#ifndef VULKAN_RENDERER_VALIDATION_H
#define VULKAN_RENDERER_VALIDATION_H

#include <GLFW/glfw3.h>
#include <vector>

namespace Core::Vulkan
{
    class VulkanApplication;

    class VulkanValidation final
    {
    public:
        VulkanValidation(const VulkanApplication* vulkanApp);
        ~VulkanValidation();

        void CreateDebugMessenger();

        inline static const std::vector<const char*> ValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        bool AreValidationLayersEnabled() const { return m_EnableValidationLayers; };

    private:
        bool CheckValidationLayerSupport();

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

        bool m_EnableValidationLayers{false};
        VkInstance m_VulkanInstance{};
        const VulkanApplication* m_VulkanApp{};

        VkDebugUtilsMessengerEXT m_DebugMessenger{};
    };
}

#endif //VULKAN_RENDERER_VALIDATION_H
