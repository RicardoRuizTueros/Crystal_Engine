#include "crystalpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Crystal
{

#define BIND_FUNCTION(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application::Application()
	{
		window = unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FUNCTION(OnEvent));
	}


	Application::~Application()
	{

	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(OnWindowClose));
		CRYSTAL_CORE_TRACE("{0}", event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		running = false;
		return true;
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