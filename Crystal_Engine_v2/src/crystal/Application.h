#pragma once

#include "Core.h"

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