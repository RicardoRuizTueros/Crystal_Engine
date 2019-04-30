#include "crystalpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Crystal
{
	Application::Application()
	{
		window = unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{

	}

	void Application::Run() 
	{
		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}
}