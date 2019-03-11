#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

using namespace std;
using namespace spdlog;

namespace Crystal {
	class CRYSTAL_API Log
	{
	public:
		static void Init();

		inline static shared_ptr<logger>& GetCoreLogger() { return coreLogger; }
		inline static shared_ptr<logger>& GetClientLogger() { return clientLogger; }
	
	private:
		static shared_ptr<logger> clientLogger;
		static shared_ptr<logger> coreLogger;
	};
}

#define CRYSTAL_CORE_ERROR(...)	Crystal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CRYSTAL_CORE_WARN(...)	Crystal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CRYSTAL_CORE_INFO(...)	Crystal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CRYSTAL_CORE_TRACE(...) Crystal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CRYSTAL_CORE_FATAL(...) Crystal::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CRYSTAL_ERROR(...)	Crystal::Log::GetClientLogger()->error(__VA_ARGS__)
#define CRYSTAL_WARN(...)	Crystal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CRYSTAL_INFO(...)	Crystal::Log::GetClientLogger()->info(__VA_ARGS__)
#define CRYSTAL_TRACE(...)	Crystal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CRYSTAL_FATAL(...)	Crystal::Log::GetClientLogger()->fatal(__VA_ARGS__)