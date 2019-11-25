#pragma once

#include "crystal/core/Input.h"

namespace Crystal
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImplementation(int keycode) override;
		virtual bool IsMouseButtonPressedImplementation(int button) override;
		virtual pair<float, float> GetMousePositionImplementation() override;
		virtual float GetMouseXPositionImplementation() override;
		virtual float GetMouseYPositionImplementation() override;
	};
}