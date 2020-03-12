#pragma once

#include "crystal/core/Core.h"
#include "crystal/core/KeyCodes.h"
#include "crystal/core/MouseCodes.h"

using namespace std;

namespace Crystal
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode keycode) { return instance->IsKeyPressedImplementation(keycode); }
		inline static bool IsMousePressed(MouseCode button) { return instance->IsMouseButtonPressedImplementation(button); }
		inline static pair<float, float> GetMousePosition() { return instance->GetMousePositionImplementation(); }
		inline float GetMouseX() { return instance->GetMouseXImplementation(); }
		inline float GetMouseY() { return instance->GetMouseYImplementation(); }

		static Scope<Input> Create();

	protected:
		Input() = default;

		Input(const Input&) = delete;
		Input& operator = (const Input&) = delete;

		virtual bool IsKeyPressedImplementation(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImplementation(MouseCode button) = 0;
		virtual pair<float, float> GetMousePositionImplementation() = 0;
		virtual float GetMouseXImplementation() = 0;
		virtual float GetMouseYImplementation() = 0;

	private:
		static Scope<Input> instance;
	};
}