#include "Window.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

Core::Window::Window()
    : m_Width(800), m_Height(600), m_Title("Vulkan window")
{
}

Core::Window::Window(const WindowData& windowData)
    : m_Width(windowData.width), m_Height(windowData.height), m_Title(windowData.title)
{
}

Core::Window::~Window()
{
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void Core::Window::Create()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
}

void Core::Window::Update([[maybe_unused]] float deltaTime)
{
    glfwPollEvents();

    
}

HWND Core::Window::GetGLFWwindowHandle() const
{
    return glfwGetWin32Window(m_pWindow);
    // return m_pWindow;
}