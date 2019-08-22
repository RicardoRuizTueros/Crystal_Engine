#include "crystalpch.h"
#include "Application.h"
#include "Input.h"

#include <glad/glad.h>

namespace Crystal
{

#define BIND_FUNCTION(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		CRYSTAL_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FUNCTION(OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application()
	{

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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack)
				layer->OnUpdate();

			imGuiLayer->Begin();
			for (Layer* layer : layerStack)
				layer->ImGuiRender();
			imGuiLayer->End();

			window->OnUpdate();
		}
	}
}