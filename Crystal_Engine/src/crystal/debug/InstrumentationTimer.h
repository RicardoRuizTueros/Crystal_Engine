#pragma once

#include <chrono>
#include <thread>

#include "crystal/debug/Instrumentor.h"

using namespace std;
using namespace chrono;

namespace Crystal
{
	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name);
		~InstrumentationTimer();

		void Stop();

	private:
		const char* name;
		time_point<steady_clock> startTime;
		bool stopped;
	};
}