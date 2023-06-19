#ifndef VULKAN_RENDERER_APPLICATION_H
#define VULKAN_RENDERER_APPLICATION_H

#include <memory>
#include <stdint.h>

#include "src/Core/Window/Window.h"
#include "src/Core/Vulkan/VulkanApplication.h"

namespace Core
{
    class Application
    {
    public:
        Application(const WindowData& windowData);
        ~Application() = default;

        void Start();

        // Rule of 5
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = default;
        Application& operator=(Application&&) = default;


    private:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Vulkan::VulkanApplication> m_VulkanApplication;

        float_t m_DeltaTime{0.0f};
    };
}

#endif //VULKAN_RENDERER_APPLICATION_H
