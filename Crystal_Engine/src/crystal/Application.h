#pragma once

#include "Window.h"
#include "Core.h"

#include "Crystal/Events/Event.h"
#include "Crystal/Events/ApplicationEvent.h"

#include "Crystal/Layers/LayerStack.h"
#include "crystal/imgui/ImGuiLayer.h"

using namespace std;

namespace Crystal
{
	class Application
	{
		public:
			Application();
			virtual ~Application() = default;
			
			void OnEvent(Event& event);
			bool OnWindowClose(WindowCloseEvent& event);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
			
			void Run();

			inline static Application& Get() { return *instance; }
			inline Window& GetWindow() { return *window; }
	private:
		static Application* instance;

		bool running = true;
		unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;

		float lastFrameTime = 0.0f;
	};

	Application* CreateApplication();
}