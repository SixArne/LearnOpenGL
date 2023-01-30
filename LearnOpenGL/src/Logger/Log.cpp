#include "pch.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_Logger{ nullptr };

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	spdlog::enable_backtrace(CONFIG_LOGGER_BACKTRACE);
	s_Logger = spdlog::stdout_color_mt(CONFIG_LOGGER_NAME);
	s_Logger->set_level(spdlog::level::trace);
}