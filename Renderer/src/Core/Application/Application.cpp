#include "Application.h"
#include "src/Core/Window/Window.h"

#include <spdlog/spdlog.h>
#include <stdint.h>
#include <chrono>

// Okay this sucks
#undef CreateWindow

Core::Application::Application()
    : m_Window(std::make_unique<Window>(600, 400, "Renderer")),
    m_VulkanApplication(std::make_unique<Vulkan::VulkanApplication>())
{
    m_Window->CreateWindow();
    m_VulkanApplication->Init();
}

void Core::Application::Start()
{
    auto lastTime = std::chrono::high_resolution_clock::now();

    const float fixedTimeStepSec{ 0.02f };
	const float desiredFPS{ 144.f };
	const int frameTimeMs{ 1000 / (int)desiredFPS };
	float lag = 0.0f;

    while (m_Window->IsRunning())
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        m_DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastTime).count();

        lastTime = currentTime;
        lag += m_DeltaTime;

        while (lag >= fixedTimeStepSec)
        {
            //m_Window->Update(fixedTimeStepSec);
            lag -= fixedTimeStepSec;
        }

        m_Window->Update(m_DeltaTime);   

        const auto sleeptime = currentTime + std::chrono::milliseconds(frameTimeMs) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleeptime);
    }
}