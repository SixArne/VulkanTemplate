#include "Window.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Core
{
    Window::Window()
    : m_Width(800), m_Height(600), m_Title("Vulkan window")
    {
    }

    Window::Window(const WindowData& windowData)
        : m_Width(windowData.width), m_Height(windowData.height), m_Title(windowData.title)
    {
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::Create()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    }

    void Window::Update([[maybe_unused]] float deltaTime)
    {
        glfwPollEvents();
    }

    GLFWwindow* Window::GetGLFWWindow() const
    {
        return m_pWindow;
    }
}
