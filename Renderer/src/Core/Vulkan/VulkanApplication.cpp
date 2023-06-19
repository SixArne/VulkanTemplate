#include "VulkanApplication.h"
#include "VulkanInstance.h"
#include "VulkanValidation.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanSwapChain.h"

#include "src/Core/Window/Window.h"
#include "src/Core/Logger/Logger.h"

Core::Vulkan::VulkanApplication::VulkanApplication()
{}

Core::Vulkan::VulkanApplication::VulkanApplication(const Window* window)
   : m_Window{window}
{
}

Core::Vulkan::VulkanApplication::~VulkanApplication()
{
    delete m_VulkanSwapChain;
    delete m_VulkanSurface;
    delete m_VulkanDevice;
    delete m_VulkanPhysicalDevice;
    delete m_VulkanValidation;
    delete m_VulkanInstance;

    L_DEBUG("Vulkan Application destroyed")
}

void Core::Vulkan::VulkanApplication::Init()
{
    L_DEBUG("Vulkan Application created")

    // Create instance (this is needed for the following vulkan components)
    m_VulkanInstance = new VulkanInstance();

    m_VulkanValidation = new VulkanValidation(this);
    m_VulkanSurface = new VulkanSurface(this);
    m_VulkanPhysicalDevice = new VulkanPhysicalDevice(this);
    m_VulkanDevice = new VulkanDevice(this);
    m_VulkanSwapChain = new VulkanSwapChain(this);
}

const VkPhysicalDevice Core::Vulkan::VulkanApplication::GetPhysicalDevice() const
{
    return m_VulkanPhysicalDevice->GetPhysicalDevice();
}

const VkInstance Core::Vulkan::VulkanApplication::GetInstance() const
{
    return m_VulkanInstance->GetInstance();
}

const Core::Vulkan::VulkanValidation* Core::Vulkan::VulkanApplication::GetValidation() const
{
    return m_VulkanValidation;
}

const VkDevice Core::Vulkan::VulkanApplication::GetDevice() const
{
    return m_VulkanDevice->GetDevice();
}

const Core::Window* Core::Vulkan::VulkanApplication::GetWindow() const
{
    return m_Window;
}

const VkSurfaceKHR Core::Vulkan::VulkanApplication::GetSurface() const
{
    return m_VulkanSurface->GetSurface();
}