#pragma once

#include "Window.h"
#include "Core.h"
#include "Crystal/Events/Event.h"
#include "Crystal/Layers/LayerStack.h"
#include "Crystal/Events/ApplicationEvent.h"
#include "crystal/imgui/ImGuiLayer.h"
#include <crystal\renderer\Shader.h>
#include <crystal\renderer\VertexBuffer.h>
#include <crystal\renderer\IndexBuffer.h>

using namespace std;

namespace Crystal
{
	class CRYSTAL_API Application
	{
		public:
			Application();
			virtual ~Application();
			
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
		unsigned int vertexArray;
		unique_ptr<VertexBuffer> vertexBuffer;
		unique_ptr<IndexBuffer> indexBuffer;
		unique_ptr<Shader> shader;
	};

	Application* CreateApplication();
}