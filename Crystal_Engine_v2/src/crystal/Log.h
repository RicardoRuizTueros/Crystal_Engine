#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;
using namespace spdlog;

namespace crystal {
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