#include <Crystal.h>

#include "platform/openGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <crystal/renderer/Texture2D.h>

using namespace Crystal;
using namespace glm;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() : Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f)
	{
		// Data & Layout
		float textureVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		BufferLayout textureLayout = {
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float2, "a_textureCoordinates" }
		};

		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_position" },
		};

		// Buffers & arrays
		textureVertexArray.reset(VertexArray::Create());

		Reference<VertexBuffer> textureVertexBuffer;
		textureVertexBuffer.reset(VertexBuffer::Create(textureVertices, sizeof(textureVertices)));
		textureVertexBuffer->SetLayout(textureLayout);
		textureVertexArray->AddVertexBuffer(textureVertexBuffer);

		uint32_t textureIndices[6] = { 0, 1, 2, 2, 3, 0};
		Reference<IndexBuffer> textureIndexBuffer;
		textureIndexBuffer.reset(IndexBuffer::Create(textureIndices, sizeof(textureIndices) / sizeof(uint32_t)));
		textureVertexArray->SetIndexBuffer(textureIndexBuffer);

		squareVertexArray.reset(VertexArray::Create());

		Reference<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->SetLayout(squareLayout);
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		// Shaders
		string textureVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec2 a_textureCoordinates;
			
			out vec2 v_textureCoordinates;

			uniform mat4 u_viewProjection;
			uniform mat4 u_transform;

			void main()
			{
				v_textureCoordinates = a_textureCoordinates;
				gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
			}
		)";

		string textureFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec2 v_textureCoordinates;

			uniform sampler2D u_texture;

			void main()
			{
				color = texture(u_texture, v_textureCoordinates);
			}
		)";

		textureShader.reset(Shader::Create(textureVertexSource, textureFragmentSource));
		checkerTexture = Texture2D::Create("assets/textures/checkerboard.png");
		logoTexture = Texture2D::Create("assets/textures/logo.png");

		dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
		dynamic_pointer_cast<OpenGLShader>(textureShader)->UploadUniformInt("u_texture", 0);

		string squareVertexSource = R"(
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

		string squareFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_position;
			
			uniform vec3 u_color;

			void main()
			{
				color = vec4(u_color, 1.0);
			}
		)";

		squareShader.reset(Shader::Create(squareVertexSource, squareFragmentSource));
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

		dynamic_pointer_cast<OpenGLShader>(squareShader)->Bind();
		dynamic_pointer_cast<OpenGLShader>(squareShader)->UploadUniformFloat3("u_color", squareShaderColor);

		for (int y = 0; y < 20; y++) 
		{
			for (int x = 0; x < 20; x++)
			{
				vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				mat4 transform = translate(mat4(1.0f), position) * scale;

				Renderer::Submit(squareShader, squareVertexArray, transform);
			}
		}

		checkerTexture->Bind();
		Renderer::Submit(textureShader, textureVertexArray, glm::scale(mat4(1.0f), vec3(1.5f)));
		
		logoTexture->Bind(1);
		Renderer::Submit(textureShader, textureVertexArray, glm::scale(mat4(1.0f), vec3(1.5f)));

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Squares color", value_ptr(squareShaderColor));
		ImGui::End();
	}

	void OnEvent(Crystal::Event& event) override
	{
		
	}

private:
	Reference<Shader> textureShader;
	Reference<VertexArray> textureVertexArray;
	Reference<Texture2D> checkerTexture, logoTexture;

	Reference<Shader> squareShader;
	Reference<VertexArray> squareVertexArray;
	vec3 squareShaderColor = { 0.2f, 0.3f, 0.8f };

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
