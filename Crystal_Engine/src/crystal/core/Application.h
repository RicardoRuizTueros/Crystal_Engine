#pragma once

#include "crystal/core/Window.h"
#include "crystal/core/Core.h"

#include "crystal/events/Event.h"
#include "crystal/events/ApplicationEvent.h"

#include "crystal/layers/LayerStack.h"
#include "crystal/imgui/ImGuiLayer.h"

using namespace std;

int main(int argc, char** argv);

namespace Crystal
{
	class Application
	{
		public:
			Application();
			virtual ~Application();
			
			void OnEvent(Event& event);
			bool OnWindowClose(WindowCloseEvent& event);
			bool OnWindowResize(WindowResizeEvent& event);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);	

			inline static Application& Get() { return *instance; }
			inline Window& GetWindow() { return *window; }
	private:
		static Application* instance;

		bool running = true;
		bool minimized = false;
		unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;
		
		friend int ::main(int argc, char** argv);
		void Run();
	};

	Application* CreateApplication();
}