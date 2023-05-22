#include "VulkanApplication.h"
#include "VulkanInstance.h"

#include <spdlog/spdlog.h>

Core::Vulkan::VulkanApplication::VulkanApplication()
{
}

Core::Vulkan::VulkanApplication::~VulkanApplication()
{
    delete m_VulkanInstance;

    spdlog::info("VulkanApplication::Destroy()");
}

void Core::Vulkan::VulkanApplication::Init()
{
    spdlog::info("VulkanApplication::Init()");

    m_VulkanInstance = new VulkanInstance();
}