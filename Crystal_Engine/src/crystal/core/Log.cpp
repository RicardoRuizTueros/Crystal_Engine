#include "crystalpch.h"
#include "crystal/core/Log.h"

#include <spdlog/sinks/basic_file_sink.h>

using namespace std;
using namespace spdlog;

namespace Crystal
{
	Reference<logger> Log::coreLogger;
	Reference<logger> Log::clientLogger;

	void Log::Init()
	{
		vector<sink_ptr> logSinks;
		
		logSinks.emplace_back(CreateReference<sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(CreateReference<sinks::basic_file_sink_mt>("Crystal.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%1] %n: %v");

		coreLogger = CreateReference<logger>("CRYSTAL", begin(logSinks), end(logSinks));
		register_logger(coreLogger);
		coreLogger->set_level(level::trace);
		coreLogger->flush_on(level::trace);

		clientLogger = CreateReference<logger>("APP", begin(logSinks), end(logSinks));
		register_logger(clientLogger);
		clientLogger->set_level(level::trace);
		clientLogger->flush_on(level::trace);
	}
}