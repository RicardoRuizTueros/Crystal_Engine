#pragma once

#include "Core.h"
#include "events/ApplicationEvent.h"
#include "crystal/Log.h"
#include "Window.h"

using namespace std;

namespace Crystal
{
	class CRYSTAL_API Application
	{
		public:
			Application();
			virtual ~Application();
			
			void Run();
	private:
		unique_ptr<Window> window;
		bool running = true;
	};

	Application* CreateApplication();
}