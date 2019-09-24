#include <Crystal.h>

#include "platform/openGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Crystal;
using namespace glm;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() : Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f)
	{
		// Data & Layout
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		float vertices2[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
		};

		BufferLayout layout2 = {
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

		vertexArray2.reset(VertexArray::Create());

		shared_ptr<VertexBuffer> vertexBuffer2;
		vertexBuffer2.reset(VertexBuffer::Create(vertices2, sizeof(vertices2)));
		vertexBuffer2->SetLayout(layout2);
		vertexArray2->AddVertexBuffer(vertexBuffer2);

		uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
		shared_ptr<IndexBuffer> indexBuffer2;
		indexBuffer2.reset(IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		vertexArray2->SetIndexBuffer(indexBuffer2);

		// Shaders
		string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;
			
			out vec3 v_position;
			out vec4 v_color;

			uniform mat4 u_viewProjection;
			uniform mat4 u_transform;

			void main()
			{
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
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

		shader.reset(Shader::Create(vertexSource, fragmentSource));

		string vertexSource2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			
			out vec3 v_position;

			uniform mat4 u_viewProjection;
			uniform mat4 u_transform;

			void main()
			{
				v_position = a_position;
				gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
			}
		)";

		string fragmentSource2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_position;
			
			uniform vec3 u_color;

			void main()
			{
				color = vec4(u_color, 1.0);
			}
		)";

		shader2.reset(Shader::Create(vertexSource2, fragmentSource2));
	}

	void OnUpdate(Timestep timestep) override
	{
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

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		camera.SetPosition(cameraPosition);
		camera.SetRotation(cameraRotation);

		Renderer::BeginScene(camera);

		mat4 scale = glm::scale(mat4(1.0f), vec3(0.1f));

		dynamic_pointer_cast<OpenGLShader>(shader2)->Bind();
		dynamic_pointer_cast<OpenGLShader>(shader2)->UploadUniformFloat3("u_color", shader2Color);

		for (int y = 0; y < 20; y++) 
		{
			for (int x = 0; x < 20; x++)
			{
				vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				mat4 transform = translate(mat4(1.0f), position) * scale;

				Renderer::Submit(shader2, vertexArray2, transform);
			}
		}

		Renderer::Submit(shader, vertexArray);

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Squares color", value_ptr(shader2Color));
		ImGui::End();
	}

	void OnEvent(Crystal::Event& event) override
	{
		
	}

private:
	shared_ptr<Shader> shader;
	shared_ptr<VertexArray> vertexArray;

	shared_ptr<Shader> shader2;
	shared_ptr<VertexArray> vertexArray2;

	OrthographicCamera camera;
	vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
	float cameraMoveSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;
	
	vec3 shader2Color = { 0.2f, 0.3f, 0.8f };
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
