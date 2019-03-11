#include "Application.h"

namespace Crystal
{
	Application::Application()
	{

	}


	Application::~Application()
	{

	}

	void Application::Run() 
	{
		WindowResizeEvent event(1280, 720);
		CRYSTAL_TRACE(event);

		while (true);
	}
}