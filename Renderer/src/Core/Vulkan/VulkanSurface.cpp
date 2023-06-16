#include "VulkanSurface.h"
#include "VulkanApplication.h"
#include "src/Core/Window/Window.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Core::Vulkan
{
    VulkanSurface::VulkanSurface(const VulkanApplication* app)
        : m_App{app}
    {

    }

    VulkanSurface::~VulkanSurface()
    {

    }

    void VulkanSurface::Init()
    {
        using Core::Window;

        auto handle = m_App->GetWindow()->GetGLFWwindowHandle();

        VkWin32SurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = handle;
        createInfo.hinstance = GetModuleHandle(nullptr);
    }
}