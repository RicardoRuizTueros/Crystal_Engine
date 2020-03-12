#include "crystalpch.h"
#include "crystal/debug/InstrumentationTimer.h"

namespace Crystal
{
	InstrumentationTimer::InstrumentationTimer(const char* name)
		: name(name), stopped(false)
	{
		startTime = chrono::steady_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!stopped)
			Stop();
	}

	void InstrumentationTimer::Stop()
	{
		auto endTime = chrono::steady_clock::now();
		auto highResStart = floatingPointMicroseconds{ startTime.time_since_epoch() };
		auto elapsedTime = chrono::time_point_cast<chrono::microseconds>(endTime).time_since_epoch() 
							- chrono::time_point_cast<chrono::microseconds>(startTime).time_since_epoch();

		Instrumentor::Get().WriteProfile({ name, highResStart, elapsedTime, this_thread::get_id() });

		stopped = true;
	}
}