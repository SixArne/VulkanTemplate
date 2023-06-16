#include <string>

#include "Core/Logger/Logger.h"

int main() {
    Core::Logger::Init();

    const std::string name{"User"};

    L_DEBUG("Hello world: {}", name);    
}