#include "VulkanSurface.h"
#include "VulkanApplication.h"
#include "src/Core/Window/Window.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <stdexcept>

#include "src/Core/Logger/Logger.h"

namespace Core::Vulkan
{
    VulkanSurface::VulkanSurface(const VulkanApplication* app)
        : m_App{app}
    {
        Init();
    }

    VulkanSurface::~VulkanSurface()
    {
        vkDestroySurfaceKHR(m_App->GetInstance(), m_Surface, nullptr);
        L_DEBUG("Validation surface destroyed");
    }

    void VulkanSurface::Init()
    {
        using Core::Window;

        auto handle = glfwGetWin32Window(m_App->GetWindow()->GetGLFWWindow());

        VkWin32SurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = handle;
        createInfo.hinstance = GetModuleHandle(nullptr);

        if (vkCreateWin32SurfaceKHR(m_App->GetInstance(), &createInfo, nullptr, &m_Surface) != VK_SUCCESS)
        {
            L_ERROR("Failed to create window surface");
        }

        L_DEBUG("Vulkan Surface created")
    }
}