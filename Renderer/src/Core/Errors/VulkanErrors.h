#ifndef VULKAN_RENDERER_CUSTOM_ERRORS_H
#define VULKAN_RENDERER_CUSTOM_ERRORS_H

#include <exception>

namespace Core::Errors
{
    class vulkan_instance_exception : public std::exception
    {
    public:
        vulkan_instance_exception(const char* message) : m_Message(message) {}
        const char* what() const noexcept override { return m_Message; }
    private:
        const char* m_Message;
    };

    class vulkan_device_exception : public std::exception
    {
    public:
        vulkan_device_exception(const char* message) : m_Message(message) {}
        const char* what() const noexcept override { return m_Message; }
    private:
        const char* m_Message;
    };
}

#endif //VULKAN_RENDERER_CUSTOM_ERRORS_H