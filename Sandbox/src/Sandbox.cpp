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

void main()
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;
}