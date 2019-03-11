#pragma once

#include "Core.h"
#include "events/ApplicationEvent.h"
#include "crystal/Log.h"

namespace Crystal
{
	class CRYSTAL_API Application
	{
		public:
			Application();
			virtual ~Application();
			
			void Run();
	};

	Application* CreateApplication();
}