//TODO - Add this to cmake

#include "Core/Application/Application.h"
#include "Core/Window/Window.h"
#include "Core/Logger/Logger.h"

#include <filesystem>

#include "Core/Vulkan/Shaders/Compiler.h"

#include <iostream>

int main() {
    using Core::Vulkan::Compiler::ShaderCompiler;
    
    Core::Logger::Init();

    std::string cwd = std::filesystem::current_path().string();

    std::vector<uint32_t> code = {};
    ShaderCompiler::SPIR_V_CompileShaderByFile("Shaders/source/diffuse.vert", EShLanguage::EShLangVertex, code);
    ShaderCompiler::SPIR_V_WriteToFile("Shaders/bin/diffuse.spv", code);
    
    WindowData windowData{ 1600, 900, "Renderer" };

    std::unique_ptr<Core::Application> app = std::make_unique<Core::Application>(windowData);
    app->Start();
  
    std::cin.get();
}