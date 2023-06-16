#ifndef VULKAN_RENDERER_WINDOW_H
#define VULKAN_RENDERER_WINDOW_H

#include <GLFW/glfw3.h>
#include <stdint.h>
#include <string>

namespace Core
{
    class Window
    {
    public:
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

        Window();
        Window(const WindowData& windowData);
        ~Window();

        void Create();
        bool IsRunning() const { return !glfwWindowShouldClose(m_pWindow); };
        Dimensions GetDimensions() const { return { m_Width, m_Height }; };
        HWND GetGLFWwindowHandle() const;
        void Update(float deltaTime);

    private:
        GLFWwindow* m_pWindow;

        uint16_t m_Width;
        uint16_t m_Height;
        std::string m_Title;
    };
}

#endif //VULKAN_RENDERER_WINDOW_H
