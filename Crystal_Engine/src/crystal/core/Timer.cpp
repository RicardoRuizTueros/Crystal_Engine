#include "crystalpch.h"
#include <chrono>

using namespace chrono;

namespace Crystal
{
	struct ProfileResult
	{
		const char* name;
		float time;
	};

	template<typename Function>

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { profileResults.push_back(profileResult); })

	class Timer
	{
	public:
		Timer(const char* name, Function&& callback)
			: name(name), callback(callback), stopped(false)
		{
			startTime = chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!stopped)
				Stop();
		}

		void Stop()
		{
			auto endTime = chrono::high_resolution_clock::now();

			long long start = time_point_cast<microseconds>(startTime).time_since_epoch().count();
			long long end = time_point_cast<microseconds>(endTime).time_since_epoch().count();

			stopped = true;

			float duration = (end - start) * 0.001f;

			callback({ name, duration });
		}

	private:
		const char* name;
		Function callback;
		time_point<steady_clock> startTime;
		bool stopped;
	};
}