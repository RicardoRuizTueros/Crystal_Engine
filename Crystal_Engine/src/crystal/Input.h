#pragma once

#include "crystal/Core.h"

using namespace std;

namespace Crystal
{
	class CRYSTAL_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImplementation(keycode); }
		inline static bool IsMousePressed(int button) { return instance->IsMouseButtonPressedImplementation(button); }
		inline static pair<float, float> GetMousePosition() { return instance->GetMousePositionImplementation(); }
		inline float GetMouseXPosition() { return instance->GetMouseXPositionImplementation(); }
		inline float GetMouseYPosition() { return instance->GetMouseYPositionImplementation(); }

	protected:
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual bool IsMouseButtonPressedImplementation(int button) = 0;
		virtual pair<float, float> GetMousePositionImplementation() = 0;
		virtual float GetMouseXPositionImplementation() = 0;
		virtual float GetMouseYPositionImplementation() = 0;

	private:
		static Input* instance;
	};
}