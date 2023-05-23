#ifndef VULKAN_RENDERER_LOGGER_H
#define VULKAN_RENDERER_LOGGER_H

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Core
{
    class Logger
    {
    public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#ifdef DEBUG
#define L_TRACE(...)	::Core::Logger::GetLogger()->trace(__VA_ARGS__);
#define L_INFO(...)		::Core::Logger::GetLogger()->info(__VA_ARGS__);
#define L_DEBUG(...)	::Core::Logger::GetLogger()->debug(__VA_ARGS__);
#define L_WARN(...)		::Core::Logger::GetLogger()->warn(__VA_ARGS__);
#define L_ERROR(...)	::Core::Logger::GetLogger()->error(__VA_ARGS__);

#define L_DUMP()		::Core::Logger::GetLogger()->dump_backtrace();

#else
#define L_TRACE(...)
#define L_INFO(...)
#define L_DEBUG(...)
#define L_WARN(...)
#define L_ERROR(...)

#define L_DUMP()

#endif

#endif // VULKAN_RENDERER_LOGGER_H