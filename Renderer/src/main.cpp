#include "Core/Application/Application.h"
#include "Core/Window/Window.h"
#include "Core/Logger/Logger.h"
#include "Core/Vulkan/Shaders/Compiler.h"

int main() {
    // Using directives to avoid namespace typing
    using Core::Logger;
    using Core::Application;
    using Core::Vulkan::Compiler::ShaderCompiler;
    using Core::Vulkan::Compiler::ShaderFileByteCode;
    
    // Setup logger
    Logger::Init();

    // Compile shader file to SPIR-V and write it back
    
   /* ShaderFileByteCode vertexShader{};
	vertexShader.shaderType = EShLangVertex;
	vertexShader.filename = "Shaders/source/diffuse.vert";

	if (ShaderCompiler::SPIR_V_CompileShaderByFile(vertexShader))
	{
		ShaderCompiler::SPIR_V_WriteToFile("Shaders/bin/diffuse_vert.spv", vertexShader.code);
	}

	ShaderFileByteCode fragmentShader{};
	fragmentShader.shaderType = EShLangFragment;
	fragmentShader.filename = "Shaders/source/diffuse.frag";

	if (ShaderCompiler::SPIR_V_CompileShaderByFile(fragmentShader))
	{
		ShaderCompiler::SPIR_V_WriteToFile("Shaders/bin/diffuse_frag.spv", fragmentShader.code);
	}*/

    auto shaderCompiler = ShaderCompiler();
    shaderCompiler.SPIR_V_CompileShadersByDirectory("Shaders");

    // Define window information
    WindowData windowData{};
    windowData.width = 1600;
    windowData.height = 900;
    windowData.title = "Renderer";

    // Start application
    std::unique_ptr<Application> app = std::make_unique<Application>(windowData);
    app->Start();
}