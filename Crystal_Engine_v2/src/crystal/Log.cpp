#include "Log.h"

namespace crystal
{
	shared_ptr<logger> Log::coreLogger;
	shared_ptr<logger> Log::clientLogger;

	void Log::Init()
	{
		set_pattern("%^`[%T] %n: %v%$");

	}
}