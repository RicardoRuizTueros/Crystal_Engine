#include "crystalpch.h"
#include "WindowsWindow.h"

namespace Crystal 
{
	static bool GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		data.title = properties.title;
		data.width = properties.width;
		data.height = properties.height;

		CRYSTAL_CORE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			CRYSTAL_CORE_ASSERT(success, "Could not intialize GLFW!");

			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)properties.width, (int)properties.height, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) 
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data.vSync;
	}
}