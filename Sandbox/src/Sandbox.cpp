#include "Crystal.h"
#include "Sandbox2D.h"

#include "crystal/core/EntryPoint.h"

using namespace Crystal;
using namespace glm;

class Sandbox : public Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Crystal::Application* CreateApplication()
{
	return new Sandbox();
}
