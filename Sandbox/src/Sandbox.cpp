#include <Crystal.h>

using namespace crystal;

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

crystal::Application* crystal::CreateApplication()
{
	return new Sandbox();
}