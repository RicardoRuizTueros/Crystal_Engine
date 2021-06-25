#include "crystalpch.h"
#include "Timer.h"

namespace Crystal
{
	Timer::Timer()
	{
		Reset();
	}
	
	void Timer::Reset()
	{
		start = high_resolution_clock::now();
	}

	float Timer::ElapsedNanoSeconds()
	{
		return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() * 0.001f * 0.001f * 0.001f;
	}
	
	float Timer::ElapsedMilliSeconds()
	{
		return ElapsedNanoSeconds() * 1000.0f;
	}
}
