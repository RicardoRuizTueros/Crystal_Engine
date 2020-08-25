#pragma once

#include <glm/glm.hpp>

#include "crystal/core/KeyCodes.h"
#include "crystal/core/MouseCodes.h"

using namespace std;
using namespace glm;

namespace Crystal
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
