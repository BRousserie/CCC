#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace CCC
{

	class Log
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

#define CCC_CORE_ERROR(...) ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)