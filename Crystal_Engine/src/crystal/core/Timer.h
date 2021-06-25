#pragma once

#include <chrono>

using namespace std;
using namespace chrono;

namespace Crystal
{
	class Timer
	{
	public:
		Timer();

		void Reset();
		float ElapsedNanoSeconds();
		float ElapsedMilliSeconds();

	private:
		time_point<high_resolution_clock> start;
	};
}
