#pragma once

#include "crystal/core/Base.h"
#include "crystal/core/KeyCodes.h"
#include "crystal/core/MouseCodes.h"

using namespace std;

namespace Crystal
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}