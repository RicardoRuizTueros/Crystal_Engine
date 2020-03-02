#include "crystalpch.h"

#include "crystal/core/Application.h"
#include "crystal/core/Log.h"
#include "crystal/core/Input.h"

#include "crystal/renderer/Renderer.h"

#include <GLFW\glfw3.h>

namespace Crystal
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		CRYSTAL_PROFILE_FUNCTION();

		CRYSTAL_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		// Window
		window = Window::Create();
		window->SetEventCallback(CRYSTAL_BIND_EVENT_FN(Application::OnEvent));

		// window->SetVSync(false);

		Renderer::Init();

		// ImGUI layer
		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
		CRYSTAL_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		CRYSTAL_PROFILE_FUNCTION();

		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		CRYSTAL_PROFILE_FUNCTION();

		layerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& event)
	{
		CRYSTAL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(CRYSTAL_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CRYSTAL_BIND_EVENT_FN(Application::OnWindowResize));

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

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		CRYSTAL_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			minimized = true;
			return false;
		}

		minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}

	void Application::Run()
	{
		CRYSTAL_PROFILE_FUNCTION();

		while (running)
		{
			CRYSTAL_PROFILE_SCOPE("Run loop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			if (!minimized)
			{
				{
					CRYSTAL_PROFILE_SCOPE("Layers OnUpdate");

					for (Layer* layer : layerStack)
						layer->OnUpdate(timestep);
				}

				imGuiLayer->Begin();
				{
					CRYSTAL_PROFILE_SCOPE("Layers OnImGuiRender")

					for (Layer* layer : layerStack)
						layer->OnImGuiRender();
				}
				imGuiLayer->End();
			}

			window->OnUpdate();
		}
	}
}