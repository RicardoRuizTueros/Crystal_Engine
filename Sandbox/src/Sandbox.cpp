#include "Crystal.h"
#include "crystal/core/EntryPoint.h"

#include "Sandbox2D.h"

namespace Crystal
{
	class Sandbox : public Application
	{
	public:
		Sandbox::Sandbox(ApplicationCommandLineArguments arguments)
		{
			// PushLayer(new ExampleLayer());
			PushLayer(new Sandbox2D());
		}

		Sandbox::~Sandbox()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArguments arguments)
	{
		return new Sandbox(arguments);
	}
}
