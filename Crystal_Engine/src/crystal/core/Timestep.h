#pragma once

namespace Crystal
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : time(time) {};
		
		operator float() const { return time; }

		float GetSeconds() const { return time; }
		float GetMiliSeconds() const { return time * 1000.0f; }
	private:
		float time;
	};
}