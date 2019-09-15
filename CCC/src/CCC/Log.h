#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace CCC
{

	class CCC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};

}

// Core log macros
#define CCC_CORE_TRACE(...) ::CCC::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CCC_CORE_INFO(...)  ::CCC::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CCC_CORE_WARN(...)  ::CCC::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CCC_CORE_ERROR(...) ::CCC::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CCC_CORE_FATAL(...) ::CCC::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CCC_CLIENT_TRACE(...) ::CCC::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CCC_CLIENT_INFO(...)  ::CCC::Log::GetClientLogger()->info(__VA_ARGS__)
#define CCC_CLIENT_WARN(...)  ::CCC::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CCC_CLIENT_ERROR(...) ::CCC::Log::GetClientLogger()->error(__VA_ARGS__)
#define CCC_CLIENT_FATAL(...) ::CCC::Log::GetClientLogger()->fatal(__VA_ARGS__)