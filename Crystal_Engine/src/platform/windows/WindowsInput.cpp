#include "crystalpch.h"

#include "platform/windows/WindowsInput.h"

#include "crystal/core/Application.h"

#include <GLFW/glfw3.h>

namespace Crystal
{
	Scope<Input> Input::instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImplementation(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImplementation(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXPositionImplementation()
	{
		auto [x, y] = GetMousePositionImplementation();
		return x;
	}

	float WindowsInput::GetMouseYPositionImplementation()
	{
		auto [x, y] = GetMousePositionImplementation();
		return y;
	}

}