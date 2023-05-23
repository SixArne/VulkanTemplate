#include "Logger.h"

std::shared_ptr<spdlog::logger> Core::Logger::s_Logger{ nullptr };

void Core::Logger::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

	spdlog::enable_backtrace(32);
	s_Logger = spdlog::stdout_color_mt("ENGINE");
	s_Logger->set_level(spdlog::level::trace);

	s_Logger->info("Logger initialized and ready for use.");
}