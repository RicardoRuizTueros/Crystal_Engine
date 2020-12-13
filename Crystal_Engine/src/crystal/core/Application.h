#pragma once

#include "crystal/core/Window.h"
#include "crystal/core/Base.h"

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
			Application(const string& name = "Crystal Application");
			virtual ~Application();

			void Close();
			
			void OnEvent(Event& event);
			bool OnWindowClose(WindowCloseEvent& event);
			bool OnWindowResize(WindowResizeEvent& event);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);	

			static Application& Get() { return *instance; }
			Window& GetWindow() { return *window; }
			ImGuiLayer* GetImGuiLayer() { return imGuiLayer; }
	private:
		static Application* instance;

		bool running = true;
		bool minimized = false;
		Scope<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;
		
		friend int ::main(int argc, char** argv);
		void Run();
	};

	Application* CreateApplication();
}
