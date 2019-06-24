#include <Crystal.h>

using namespace Crystal;

class ExampleLayer : public Crystal::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		CRYSTAL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Crystal::Event& event) override
	{
		CRYSTAL_TRACE("{0}", event);
	}
};

class Sandbox : public Application
{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
			PushOverlay(new ImGuiLayer());
		}

		~Sandbox()
		{

		}
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}