#include "Log.h"

namespace Crystal
{
	shared_ptr<logger> Log::coreLogger;
	shared_ptr<logger> Log::clientLogger;

	void Log::Init()
	{
		set_pattern("%^ [%T] %n: %v%$");

		coreLogger = stdout_color_mt("Crystal");
		coreLogger->set_level(level::trace);

		clientLogger = stdout_color_mt("Sandbox");
		clientLogger->set_level(level::trace);
	}
}