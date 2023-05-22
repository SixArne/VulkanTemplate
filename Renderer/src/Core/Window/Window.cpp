#include "Window.h"

Core::Window::Window()
    : m_Width(800), m_Height(600), m_Title("Vulkan window")
{
}

Core::Window::Window(uint16_t width, uint16_t height, const std::string& title)
    : m_Width(width), m_Height(height), m_Title(title)
{
}

Core::Window::~Window()
{
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

void Core::Window::CreateWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
}

void Core::Window::Update([[maybe_unused]] float deltaTime)
{
    glfwPollEvents();
}