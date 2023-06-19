#include "Window.h"

#include <stdint.h>
#include <string>
#include <memory>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Core
{
    class Window::WindowImpl 
    {
    public:
        WindowImpl();
        WindowImpl(const WindowData& windowData);
        ~WindowImpl();

        void Create();
        bool IsRunning() const;
        void Update(float deltaTime);

        Dimensions GetDimensions() const;
        GLFWwindow* GetGLFWWindow() const;

    private:
        GLFWwindow* m_pWindow;

        uint16_t m_Width;
        uint16_t m_Height;
        std::string m_Title;
    };
}

namespace Core
{
    Window::WindowImpl::WindowImpl()
        : m_Width(800), m_Height(600), m_Title("Vulkan window")
    {

    }

    Window::WindowImpl::WindowImpl(const WindowData& windowData)
        : m_Width(windowData.width), m_Height(windowData.height), m_Title(windowData.title)
    {

    }

    Window::WindowImpl::~WindowImpl()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    void Window::WindowImpl::Create()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    }

    bool Window::WindowImpl::IsRunning() const  
    {
        return !glfwWindowShouldClose(m_pWindow);
    }

    Dimensions Window::WindowImpl::GetDimensions() const 
    {
        return {m_Width, m_Height};
    }

    GLFWwindow* Window::WindowImpl::GetGLFWWindow() const
    {
        return m_pWindow;
    }

    void Window::WindowImpl::Update(float)
    {
        glfwPollEvents();
    }
}

namespace Core
{
    Window::Window()
        : m_Impl{std::make_unique<WindowImpl>()}
    {
    }

    Window::Window(const WindowData& windowData)
        : m_Impl{std::make_unique<WindowImpl>(windowData)}
    {
    }

    Window::~Window()
    {
    }

    void Window::Create()
    {
        m_Impl->Create();
    }

    void Window::Update(float dt)
    {
        m_Impl->Update(dt);
    }

    GLFWwindow* Window::GetGLFWWindow() const
    {
        return m_Impl->GetGLFWWindow();
    }

    bool Window::IsRunning() const
    {
        return m_Impl->IsRunning();
    }

    Dimensions Window::GetDimensions() const
    {
        return m_Impl->GetDimensions();
    }
}
