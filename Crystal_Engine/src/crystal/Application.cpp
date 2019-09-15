#include "crystalpch.h"
#include "Application.h"

#include "crystal/renderer/Renderer.h"

namespace Crystal
{

#define BIND_FUNCTION(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	// Camera
	: camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		CRYSTAL_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		// Window
		window = unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FUNCTION(OnEvent));

		// ImGUI layer
		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);

		// Data & Layout
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		float vertices_2[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
		};

		BufferLayout layout_2 = {
			{ ShaderDataType::Float3, "a_position" },
		};

		// Buffers & arrays
		vertexArray.reset(VertexArray::Create());
		
		shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		vertexArray_2.reset(VertexArray::Create());

		shared_ptr<VertexBuffer> vertexBuffer_2;
		vertexBuffer_2.reset(VertexBuffer::Create(vertices_2, sizeof(vertices_2)));
		vertexBuffer_2->SetLayout(layout_2);
		vertexArray_2->AddVertexBuffer(vertexBuffer_2);

		uint32_t indices_2[6] = { 0, 1, 2, 2, 3, 0 };
		shared_ptr<IndexBuffer> indexBuffer_2;
		indexBuffer_2.reset(IndexBuffer::Create(indices_2, sizeof(indices_2) / sizeof(uint32_t)));
		vertexArray_2->SetIndexBuffer(indexBuffer_2);

		// Shaders
		string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;
			
			out vec3 v_position;
			out vec4 v_color;

			uniform mat4 u_viewProjection;

			void main()
			{
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_viewProjection * vec4(a_position, 1.0);
			}
		)";

		string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_position;
			in vec4 v_color;

			void main()
			{
				color = v_color;
			}
		)";

		shader.reset(new Shader(vertexSource, fragmentSource));

		string vertexSource_2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			
			out vec3 v_position;

			uniform mat4 u_viewProjection;

			void main()
			{
				v_position = a_position;
				gl_Position = u_viewProjection * vec4(a_position, 1.0);
			}
		)";

		string fragmentSource_2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		shader_2.reset(new Shader(vertexSource_2, fragmentSource_2));
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

			RenderCommand::Clear();

			camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			camera.SetRotation(45.0f);

			Renderer::BeginScene(camera);
			
			Renderer::Submit(shader_2, vertexArray_2);
			Renderer::Submit(shader, vertexArray);

			Renderer::EndScene();

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