#include <Crystal.h>

using namespace Crystal;

class Sandbox : public Application
{
	public:
		Sandbox()
		{

		}

		~Sandbox()
		{

		}
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}