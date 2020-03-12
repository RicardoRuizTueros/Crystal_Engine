#pragma once

#include "crystal/core/Input.h"

namespace Crystal
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImplementation(KeyCode keycode) override;
		virtual bool IsMouseButtonPressedImplementation(MouseCode button) override;
		virtual pair<float, float> GetMousePositionImplementation() override;
		virtual float GetMouseXImplementation() override;
		virtual float GetMouseYImplementation() override;
	};
}