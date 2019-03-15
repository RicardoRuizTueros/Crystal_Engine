#include "crystalpch.h"
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

		if (event.IsCategory(EventCategoryApplication))
		{
			CRYSTAL_TRACE(event);
		}

		if (event.IsCategory(EventCategoryInput))
		{
			CRYSTAL_TRACE(event);
		}

		while (true);
	}
}