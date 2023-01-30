#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#ifdef DEBUG
#define L_CREATE()				::Log::Init()

#define L_TRACE(...)			::Log::GetLogger()->trace(__VA_ARGS__)
#define L_INFO(...)				::Log::GetLogger()->info(__VA_ARGS__)
#define L_DEBUG(...)			::Log::GetLogger()->debug(__VA_ARGS__)
#define L_WARN(...)				::Log::GetLogger()->warn(__VA_ARGS__)
#define L_ERROR(...)			::Log::GetLogger()->error(__VA_ARGS__)

#define L_DUMP()				::Log::GetLogger()->dump_backtrace();

#else
#define L_CREATE()

#define L_TRACE(...)
#define L_INFO(...)
#define L_DEBUG(...)
#define L_WARN(...)	
#define L_ERROR(...)

#define L_DUMP()
#endif

#endif
