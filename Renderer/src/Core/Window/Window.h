#ifndef VULKAN_RENDERER_WINDOW_H
#define VULKAN_RENDERER_WINDOW_H

#include <string>
#include <memory>

struct GLFWwindow;

struct WindowData
{
    uint16_t width      {800};
    uint16_t height     {600};
    std::string title   {"Vulkan window"};
};

struct Dimensions
{
    uint16_t width;
    uint16_t height;
};

namespace Core
{
    class Window
    {
    public:
        Window();
        Window(const WindowData& windowData);
        ~Window();

        void Create();
        bool IsRunning() const;
        Dimensions GetDimensions() const;
        GLFWwindow* GetGLFWWindow() const;
        void Update(float deltaTime);

    private:
        class WindowImpl;
        std::unique_ptr<WindowImpl> m_Impl;
    };
}

#endif //VULKAN_RENDERER_WINDOW_H
