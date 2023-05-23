//TODO - Add this to cmake

#include "Core/Application/Application.h"
#include "Core/Window/Window.h"
#include "Core/Logger/Logger.h"

int main() {
    Core::Logger::Init();

    Core::Window::WindowData windowData{ 1600, 900, "Renderer" };

    std::unique_ptr<Core::Application> app = std::make_unique<Core::Application>(windowData);
    app->Start();
}