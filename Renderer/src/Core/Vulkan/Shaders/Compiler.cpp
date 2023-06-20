#include "Compiler.h"

#include <array>

// Cause fuck the maintainers of this library.
#pragma warning(push)
#pragma warning(disable: 4458)
#pragma warning(disable: 4457)
#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>
#pragma warning(pop)

#include "src/Core/Logger/Logger.h"

namespace Core::Vulkan::Compiler
{
    bool ShaderCompiler::SPIR_V_CompileShaderByFile(const std::string& filename, EShLanguage shaderType, SPIR_V& spirvCode)
    {
        auto shaderCode = ShaderLoader::ReadShaderFile(filename);
        if (!shaderCode.empty())
        {
            glslang::InitializeProcess();

            glslang::TShader shader(shaderType);

            std::array<const char*, 1> shaderStrings{};
            shaderStrings[0] = shaderCode.c_str();

            shader.setStrings(shaderStrings.data(), static_cast<int>(shaderStrings.size()));

            int clientInputSemanticsVersion = 100;
            glslang::EShTargetClientVersion vulkanClientVersion = glslang::EShTargetVulkan_1_3;
            glslang::EShTargetLanguageVersion targetVersion = glslang::EShTargetSpv_1_6;
            shader.setEnvTarget(glslang::EshTargetSpv, targetVersion);
            shader.setEnvClient(glslang::EShClientVulkan, vulkanClientVersion);
            shader.setEntryPoint("main");

            TBuiltInResource resources{};
            resources = InitResources();

            const int defaultVersion = 100;

            EShMessages messages = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);


            if (!shader.parse(&resources, defaultVersion, false, messages)) {
                puts(shader.getInfoLog());
                puts(shader.getInfoDebugLog());
                return false;  // shader failed to compile
            }

            glslang::TProgram program;
            program.addShader(&shader);

            if (!program.link(messages)) {
                puts(program.getInfoLog());
                puts(program.getInfoDebugLog());
                return false;  // program failed to link
            }

            glslang::GlslangToSpv(*program.getIntermediate(shaderType), spirvCode);

            return true;
        }

        return false;
    }

    TBuiltInResource ShaderCompiler::InitResources()
    {
        TBuiltInResource Resources{};

        Resources.maxLights = 32;
        Resources.maxClipPlanes = 6;
        Resources.maxTextureUnits = 32;
        Resources.maxTextureCoords = 32;
        Resources.maxVertexAttribs = 64;
        Resources.maxVertexUniformComponents = 4096;
        Resources.maxVaryingFloats = 64;
        Resources.maxVertexTextureImageUnits = 32;
        Resources.maxCombinedTextureImageUnits = 80;
        Resources.maxTextureImageUnits = 32;
        Resources.maxFragmentUniformComponents = 4096;
        Resources.maxDrawBuffers = 32;
        Resources.maxVertexUniformVectors = 128;
        Resources.maxVaryingVectors = 8;
        Resources.maxFragmentUniformVectors = 16;
        Resources.maxVertexOutputVectors = 16;
        Resources.maxFragmentInputVectors = 15;
        Resources.minProgramTexelOffset = -8;
        Resources.maxProgramTexelOffset = 7;
        Resources.maxClipDistances = 8;
        Resources.maxComputeWorkGroupCountX = 65535;
        Resources.maxComputeWorkGroupCountY = 65535;
        Resources.maxComputeWorkGroupCountZ = 65535;
        Resources.maxComputeWorkGroupSizeX = 1024;
        Resources.maxComputeWorkGroupSizeY = 1024;
        Resources.maxComputeWorkGroupSizeZ = 64;
        Resources.maxComputeUniformComponents = 1024;
        Resources.maxComputeTextureImageUnits = 16;
        Resources.maxComputeImageUniforms = 8;
        Resources.maxComputeAtomicCounters = 8;
        Resources.maxComputeAtomicCounterBuffers = 1;
        Resources.maxVaryingComponents = 60;
        Resources.maxVertexOutputComponents = 64;
        Resources.maxGeometryInputComponents = 64;
        Resources.maxGeometryOutputComponents = 128;
        Resources.maxFragmentInputComponents = 128;
        Resources.maxImageUnits = 8;
        Resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
        Resources.maxCombinedShaderOutputResources = 8;
        Resources.maxImageSamples = 0;
        Resources.maxVertexImageUniforms = 0;
        Resources.maxTessControlImageUniforms = 0;
        Resources.maxTessEvaluationImageUniforms = 0;
        Resources.maxGeometryImageUniforms = 0;
        Resources.maxFragmentImageUniforms = 8;
        Resources.maxCombinedImageUniforms = 8;
        Resources.maxGeometryTextureImageUnits = 16;
        Resources.maxGeometryOutputVertices = 256;
        Resources.maxGeometryTotalOutputComponents = 1024;
        Resources.maxGeometryUniformComponents = 1024;
        Resources.maxGeometryVaryingComponents = 64;
        Resources.maxTessControlInputComponents = 128;
        Resources.maxTessControlOutputComponents = 128;
        Resources.maxTessControlTextureImageUnits = 16;
        Resources.maxTessControlUniformComponents = 1024;
        Resources.maxTessControlTotalOutputComponents = 4096;
        Resources.maxTessEvaluationInputComponents = 128;
        Resources.maxTessEvaluationOutputComponents = 128;
        Resources.maxTessEvaluationTextureImageUnits = 16;
        Resources.maxTessEvaluationUniformComponents = 1024;
        Resources.maxTessPatchComponents = 120;
        Resources.maxPatchVertices = 32;
        Resources.maxTessGenLevel = 64;
        Resources.maxViewports = 16;
        Resources.maxVertexAtomicCounters = 0;
        Resources.maxTessControlAtomicCounters = 0;
        Resources.maxTessEvaluationAtomicCounters = 0;
        Resources.maxGeometryAtomicCounters = 0;
        Resources.maxFragmentAtomicCounters = 8;
        Resources.maxCombinedAtomicCounters = 8;
        Resources.maxAtomicCounterBindings = 1;
        Resources.maxVertexAtomicCounterBuffers = 0;
        Resources.maxTessControlAtomicCounterBuffers = 0;
        Resources.maxTessEvaluationAtomicCounterBuffers = 0;
        Resources.maxGeometryAtomicCounterBuffers = 0;
        Resources.maxFragmentAtomicCounterBuffers = 1;
        Resources.maxCombinedAtomicCounterBuffers = 1;
        Resources.maxAtomicCounterBufferSize = 16384;
        Resources.maxTransformFeedbackBuffers = 4;
        Resources.maxTransformFeedbackInterleavedComponents = 64;
        Resources.maxCullDistances = 8;
        Resources.maxCombinedClipAndCullDistances = 8;
        Resources.maxSamples = 4;
        Resources.maxMeshOutputVerticesNV = 256;
        Resources.maxMeshOutputPrimitivesNV = 512;
        Resources.maxMeshWorkGroupSizeX_NV = 32;
        Resources.maxMeshWorkGroupSizeY_NV = 1;
        Resources.maxMeshWorkGroupSizeZ_NV = 1;
        Resources.maxTaskWorkGroupSizeX_NV = 32;
        Resources.maxTaskWorkGroupSizeY_NV = 1;
        Resources.maxTaskWorkGroupSizeZ_NV = 1;
        Resources.maxMeshViewCountNV = 4;

        Resources.limits.nonInductiveForLoops = 1;
        Resources.limits.whileLoops = 1;
        Resources.limits.doWhileLoops = 1;
        Resources.limits.generalUniformIndexing = 1;
        Resources.limits.generalAttributeMatrixVectorIndexing = 1;
        Resources.limits.generalVaryingIndexing = 1;
        Resources.limits.generalSamplerIndexing = 1;
        Resources.limits.generalVariableIndexing = 1;
        Resources.limits.generalConstantMatrixVectorIndexing = 1;

        return Resources;
    }

    bool ShaderCompiler::SPIR_V_CompileShadersByDirectory(const std::string& directory, EShLanguage shaderType, std::vector<SPIR_V>& spirvCode)
    {
        return true;
    }

	bool ShaderCompiler::SPIR_V_WriteToFile(const std::string& filename, SPIR_V& spirvcode)
	{
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open())
        {
            file.write(reinterpret_cast<const char*>(spirvcode.data()), spirvcode.size() * sizeof(uint32_t));
            file.close();

            L_DEBUG("SPIR-V file written as: {}", filename);

            return true;
        }
        else
        {
            L_DEBUG("Failed to open and write SPIR-V file: {}", filename);

            return false;
        }
	}

    std::string ShaderLoader::ReadShaderFile(const std::string& filename)
    {
        std::string output{};
        if (std::ifstream file{filename, std::ios::binary})
        {
            output.assign(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
            );
        }
        else
        {
            L_ERROR("Failed to read shader file: {}", filename);
            return output;
        }

        return output;
    }

	ShaderLoader::ShaderFile ShaderLoader::SPIR_V_LoadShaderByFile(const std::string& filename)
	{
        return { "", std::vector<char>() };
	}

    std::vector<ShaderLoader::ShaderFile> ShaderLoader::SPIR_V_LoadShadersByDirectory(const std::string& directory)
    {
        return std::vector<ShaderLoader::ShaderFile>{};
	}

}