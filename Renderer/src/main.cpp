//TODO - Add this to cmake

#include "Core/Application/Application.h"

int main() {
    std::unique_ptr<Core::Application> app = std::make_unique<Core::Application>();
    app->Start();
}