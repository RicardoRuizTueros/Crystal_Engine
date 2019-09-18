#include "crystalpch.h"
#include "Application.h"

#include "crystal/renderer/Renderer.h"

#include <GLFW\glfw3.h>
#include <crystal\core\Timestep.h>

namespace Crystal
{

#define BIND_FUNCTION(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		CRYSTAL_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		// Window
		window = unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FUNCTION(OnEvent));
		window->SetVSync(false);

		// ImGUI layer
		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}


	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(OnWindowClose));

		for (auto iterator = layerStack.end(); iterator != layerStack.begin(); )
		{
			(*--iterator)->OnEvent(event);
			if (event.handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		running = false;
		return true;
	}

	void Application::Run() 
	{
		while (running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			for (Layer* layer : layerStack)
				layer->OnUpdate(timestep);

			imGuiLayer->Begin();
			for (Layer* layer : layerStack)
				layer->ImGuiRender();
			imGuiLayer->End();

			window->OnUpdate();
		}
	}
}