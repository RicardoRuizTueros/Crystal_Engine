#pragma once

#include "Core.h"

namespace crystal 
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