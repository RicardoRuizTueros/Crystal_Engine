#pragma once

#include "crystal/core/Base.h"
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

using namespace std;
using namespace spdlog;

namespace Crystal {
	class Log
	{
	public:
		static void Init();

		static Reference<logger>& GetCoreLogger() { return coreLogger; }
		static Reference<logger>& GetClientLogger() { return clientLogger; }
	
	private:
		static Reference<logger> clientLogger;
		static Reference<logger> coreLogger;
	};
}

#define CRYSTAL_CORE_ERROR(...)	Crystal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CRYSTAL_CORE_WARNING(...)	Crystal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CRYSTAL_CORE_INFO(...)	Crystal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CRYSTAL_CORE_TRACE(...) Crystal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CRYSTAL_CORE_CRITICAL(...) Crystal::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CRYSTAL_ERROR(...)	Crystal::Log::GetClientLogger()->error(__VA_ARGS__)
#define CRYSTAL_WARN(...)	Crystal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CRYSTAL_INFO(...)	Crystal::Log::GetClientLogger()->info(__VA_ARGS__)
#define CRYSTAL_TRACE(...)	Crystal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CRYSTAL_CRITICAL(...)	Crystal::Log::GetClientLogger()->critical(__VA_ARGS__)
