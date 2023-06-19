#include "VulkanSwapChain.h"

#include <vector>
#include <limits>
#include <algorithm>
#include <GLFW/glfw3.h>

#include "src/Core/Vulkan/VulkanApplication.h"
#include "VulkanApplication.h"
#include "src/Core/Window/Window.h"
#include "Helpers/Helpers.h"

#include "src/Core/Logger/Logger.h"

namespace Core::Vulkan
{
    VulkanSwapChain::VulkanSwapChain(const VulkanApplication* app)
        : m_VulkanApp{app}
    {
        Init();
        CreateImageViews();

        L_DEBUG("Vulkan Swapchain created")
    }

    VulkanSwapChain::~VulkanSwapChain()
    {
        vkDestroySwapchainKHR(m_VulkanApp->GetDevice(), m_SwapChain, nullptr);

        for (auto imageView: m_SwapChainImageViews)
        {
            vkDestroyImageView(m_VulkanApp->GetDevice(), imageView, nullptr);
        }
    }

    void VulkanSwapChain::Init()
    {
        Helpers::SwapChainSupportDetails swapChainSupport = Helpers::QuerySwapChainSupport(m_VulkanApp->GetPhysicalDevice(), m_VulkanApp->GetSurface());

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = std::max(swapChainSupport.capabilities.minImageCount + 1, swapChainSupport.capabilities.maxImageCount);

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = m_VulkanApp->GetSurface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        Helpers::QueueFamilyIndices indices = Helpers::FindQueueFamilies(m_VulkanApp->GetPhysicalDevice(), m_VulkanApp->GetSurface());
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        // TODO: If seperate queue make them exclusive later
        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // TODO: Change this later to blend windows
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE; // TODO: Disable this later to see fps difference
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(m_VulkanApp->GetDevice(), &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS)
        {
            L_ERROR("Failed to create swap chain");
            throw std::runtime_error("Failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(m_VulkanApp->GetDevice(), m_SwapChain, &imageCount, nullptr);
        m_SwapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(m_VulkanApp->GetDevice(), m_SwapChain, &imageCount, m_SwapChainImages.data());

        m_SwapChainExtent = extent;
        m_SwapChainFormat = surfaceFormat.format;

        m_SwapChainImageViews.resize(m_SwapChainImages.size());
    }

    void VulkanSwapChain::CreateImageViews()
    {
        for (auto swapChainImage: m_SwapChainImages)
        {
            VkImageView view = Helpers::CreateImageView(m_VulkanApp->GetDevice(), swapChainImage, m_SwapChainFormat);
            m_SwapChainImageViews.emplace_back(view);
        }
    }

    VkSurfaceFormatKHR VulkanSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return availableFormat;
            }
        }

        return availableFormats[0]; // fallback
    }

    VkPresentModeKHR VulkanSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }
        else
        {
            int width{}, height{};
            // TODO: extract this to decouple glfw
            glfwGetFramebufferSize(m_VulkanApp->GetWindow()->GetGLFWWindow(), &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }
}