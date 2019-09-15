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
#include <crystal/renderer/VertexArray.h>

#include "crystal/renderer/OrthographicCamera.h"

using namespace std;

namespace Crystal
{
	class CRYSTAL_API Application
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
		
		shared_ptr<Shader> shader;
		shared_ptr<VertexArray> vertexArray;

		shared_ptr<Shader> shader_2;
		shared_ptr<VertexArray> vertexArray_2;

		OrthographicCamera camera;
	};

	Application* CreateApplication();
}