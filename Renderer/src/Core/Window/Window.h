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
        Window();
        Window(uint16_t width = 800, uint16_t height = 600, const std::string& title = "Vulkan window");
        ~Window();

        void CreateWindow();
        bool IsRunning() const { return !glfwWindowShouldClose(m_pWindow); };
        void Update(float deltaTime);

    private:
        GLFWwindow* m_pWindow;

        uint16_t m_Width;
        uint16_t m_Height;
        std::string m_Title;
    };
}

#endif //VULKAN_RENDERER_WINDOW_H
