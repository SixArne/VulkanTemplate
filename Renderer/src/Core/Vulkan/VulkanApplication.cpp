#include "VulkanApplication.h"
#include "VulkanInstance.h"
#include "VulkanValidation.h"
#include "VulkanPhysicalDevice.h"

#include <spdlog/spdlog.h>

Core::Vulkan::VulkanApplication::VulkanApplication()
{
}

Core::Vulkan::VulkanApplication::~VulkanApplication()
{
    delete m_VulkanValidation;
    delete m_VulkanInstance;

    spdlog::info("VulkanApplication::Destroy()");
}

void Core::Vulkan::VulkanApplication::Init()
{
    spdlog::info("VulkanApplication::Init()");

    // Create instance (this is needed for the following vulkan components)
    m_VulkanInstance = new VulkanInstance();

    m_VulkanValidation = new VulkanValidation(m_VulkanInstance->GetInstance());
    m_VulkanPhysicalDevice = new VulkanPhysicalDevice(m_VulkanInstance->GetInstance());
}