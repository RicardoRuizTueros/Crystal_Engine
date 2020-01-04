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
	
	}
	
	void Sandbox2D::OnDetach()
	{
	
	}
	
	void Sandbox2D::OnUpdate(Timestep timestep)
	{
		cameraController.OnUpdate(timestep);

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(cameraController.GetCamera());
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		// TODO: Add these functions - Shader::SetMat4, Shader::SetFloat4
		/*dynamic_pointer_cast<OpenGLShader>(flatColorShader)->Bind();*/
		//dynamic_pointer_cast<OpenGLShader>(flatColorShader)->UploadUniformFloat4("u_color", squareColor);
		
		Renderer2D::EndScene();
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