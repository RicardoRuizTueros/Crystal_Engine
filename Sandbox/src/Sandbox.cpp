#include "Crystal.h"
#include "Sandbox2D.h"

#include "crystal/core/EntryPoint.h"

using namespace Crystal;
using namespace glm;

class Sandbox : public Application
{
public:
	Sandbox(Crystal::ApplicationCommandLineArguments arguments)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Crystal::Application* CreateApplication(Crystal::ApplicationCommandLineArguments arguments)
{
	return new Sandbox(arguments);
}
