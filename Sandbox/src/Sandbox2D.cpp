#include "Sandbox2D.h"

#include "platform/openGL/OpenGLShader.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

namespace Crystal
{
	Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f)
	{
	}
	
	void Sandbox2D::OnAttach()
	{
		squareVertexArray = VertexArray::Create();

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Reference<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_Position" },
		});
		
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}
	
	void Sandbox2D::OnDetach()
	{
	
	}
	
	void Sandbox2D::OnUpdate(Timestep timestep)
	{
		cameraController.OnUpdate(timestep);

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(cameraController.GetCamera());
		dynamic_pointer_cast<OpenGLShader>(flatColorShader)->Bind();
		dynamic_pointer_cast<OpenGLShader>(flatColorShader)->UploadUniformFloat4("u_color", squareColor);
		
		Renderer::Submit(flatColorShader, squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		Renderer::EndScene();
	}
	
	void Sandbox2D::OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
		ImGui::End();
	}

	void Sandbox2D::OnEvent(Event& event)
	{
		cameraController.OnEvent(event);
	}


}