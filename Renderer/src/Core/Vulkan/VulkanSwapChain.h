#ifndef VULKAN_RENDERER_VULKAN_SWAPCHAIN_H
#define VULKAN_RENDERER_VULKAN_SWAPCHAIN_H

#include <vector>
#include <GLFW/glfw3.h>

namespace Core::Vulkan
{
    class VulkanApplication;

    class VulkanSwapChain final
    {
    public:
        VulkanSwapChain(const VulkanApplication* app);
        ~VulkanSwapChain();

        VulkanSwapChain(const VulkanSwapChain& other) = delete;
        VulkanSwapChain(VulkanSwapChain&& other) = delete;
        VulkanSwapChain& operator=(const VulkanSwapChain& other) = delete;
        VulkanSwapChain& operator=(VulkanSwapChain&& other) = delete;

        const VkSwapchainKHR GetSwapChain() const { return m_SwapChain;};

    private:
        void Init();
        void CreateImageViews();

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        const VulkanApplication* m_VulkanApp{};

        VkSwapchainKHR m_SwapChain{};
        VkFormat m_SwapChainFormat{};
        VkExtent2D m_SwapChainExtent{};

        std::vector<VkImage> m_SwapChainImages{};
        std::vector<VkImageView> m_SwapChainImageViews{};
    };
}

#endif