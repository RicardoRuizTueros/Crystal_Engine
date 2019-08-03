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
		if (Input::IsKeyPressed(CRYSTAL_KEY_A))
			CRYSTAL_TRACE("Pressed {0} (polling)", (char)CRYSTAL_KEY_A);
	}

	void OnEvent(Crystal::Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed)
		{
			KeyPressedEvent& keyEvent = (KeyPressedEvent&)event;
			CRYSTAL_TRACE("Pressed {0} (event)", (char)keyEvent.GetKeyCode());
		}
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