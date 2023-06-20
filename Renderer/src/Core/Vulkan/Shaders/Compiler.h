#ifndef VULKAN_RENDERER_SHADER_COMPILER_H
#define VULKAN_RENDERER_SHADER_COMPILER_H

#include <vector>
#include <string>

#pragma warning(push)
#pragma warning(disable: 4458)
#pragma warning(disable: 4457)
#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>
#pragma warning(pop)

namespace Core::Vulkan::Compiler
{
    class ShaderCompiler final
    {
    public:
        using SPIR_V = std::vector<uint32_t>;

        static bool SPIR_V_CompileShadersByDirectory(const std::string& directory, EShLanguage shaderType, std::vector<SPIR_V>& spirvCode);
        static bool SPIR_V_CompileShaderByFile(const std::string& filename, EShLanguage shaderType, SPIR_V& spirvCode);

        static bool SPIR_V_WriteToFile(const std::string& filename, SPIR_V& spirvcode);

    private:
        static TBuiltInResource InitResources();
    };

    class ShaderLoader final
    {
    public:
        using ShaderFile = std::pair<std::string, std::vector<char>>;
        static ShaderFile SPIR_V_LoadShaderByFile(const std::string& filename);
        static std::vector<ShaderFile> SPIR_V_LoadShadersByDirectory(const std::string& directory);

        static std::string ReadShaderFile(const std::string& filename);
    };
}

#endif