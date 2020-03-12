#include "crystalpch.h"

#include "platform/windows/WindowsInput.h"

#include "crystal/core/Application.h"

#include <GLFW/glfw3.h>

namespace Crystal
{
	bool WindowsInput::IsKeyPressedImplementation(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImplementation(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

		return state == GLFW_PRESS;
	}

	pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImplementation()
	{
		auto [x, y] = GetMousePositionImplementation();
		return x;
	}

	float WindowsInput::GetMouseYImplementation()
	{
		auto [x, y] = GetMousePositionImplementation();
		return y;
	}

}