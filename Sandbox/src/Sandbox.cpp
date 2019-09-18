#include <Crystal.h>

using namespace Crystal;
using namespace glm;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() : Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
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

	void OnUpdate(Timestep timestep) override
	{
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		CRYSTAL_CORE_TRACE("Delta time: {0}", timestep);

		if (Input::IsKeyPressed(CRYSTAL_KEY_LEFT))
			cameraPosition.x -= cameraMoveSpeed * timestep;
		else if (Input::IsKeyPressed(CRYSTAL_KEY_RIGHT))
			cameraPosition.x += cameraMoveSpeed * timestep;

		if (Input::IsKeyPressed(CRYSTAL_KEY_DOWN))
			cameraPosition.y -= cameraMoveSpeed * timestep;
		else if (Input::IsKeyPressed(CRYSTAL_KEY_UP))
			cameraPosition.y += cameraMoveSpeed * timestep;

		if (Input::IsKeyPressed(CRYSTAL_KEY_Q))
			cameraRotation += cameraRotationSpeed * timestep;
		else if (Input::IsKeyPressed(CRYSTAL_KEY_E))
			cameraRotation -= cameraRotationSpeed * timestep;

		camera.SetPosition(cameraPosition);
		camera.SetRotation(cameraRotation);

		Renderer::BeginScene(camera);

		Renderer::Submit(shader_2, vertexArray_2);
		Renderer::Submit(shader, vertexArray);

		Renderer::EndScene();
	}

	void OnEvent(Crystal::Event& event) override
	{
		
	}

private:
	shared_ptr<Shader> shader;
	shared_ptr<VertexArray> vertexArray;

	shared_ptr<Shader> shader_2;
	shared_ptr<VertexArray> vertexArray_2;

	OrthographicCamera camera;
	vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
	float cameraMoveSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;
};

class Sandbox : public Application
{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
		}

		~Sandbox()
		{

		}
};

Crystal::Application* Crystal::CreateApplication()
{
	return new Sandbox();
}