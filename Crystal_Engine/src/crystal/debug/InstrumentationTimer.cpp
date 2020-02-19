#include "crystalpch.h"
#include "crystal/debug/InstrumentationTimer.h"

namespace Crystal
{
	InstrumentationTimer::InstrumentationTimer(const char* name)
		: name(name), stopped(false)
	{
		startTime = chrono::high_resolution_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTime = chrono::high_resolution_clock::now();

		long long start = time_point_cast<microseconds>(startTime).time_since_epoch().count();
		long long end = time_point_cast<microseconds>(endTime).time_since_epoch().count();
		uint32_t threadID = hash<thread::id>{}(this_thread::get_id());

		Instrumentor::Get().WriteProfile({ name, start, end, threadID });

		stopped = true;
	}
}