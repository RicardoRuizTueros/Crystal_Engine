#include "Sandbox2D.h"

#include "platform/openGL/OpenGLShader.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

using namespace glm;



namespace Crystal
{
	Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f)
	{

	}
	
	void Sandbox2D::OnAttach()
	{
		checkerTexture = Texture2D::Create("assets/textures/checkerboard.png");
	}
	
	void Sandbox2D::OnDetach()
	{
	
	}
	
	void Sandbox2D::OnUpdate(Timestep timestep)
	{
		PROFILE_SCOPE("Sandbox2D::OnUpdate");
		
		{
			PROFILE_SCOPE("CameraController::OnUpdate");
			cameraController.OnUpdate(timestep);
		}
		
		{
			PROFILE_SCOPE("RenderCommand::OnUpdate");
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();
		}

		{
			PROFILE_SCOPE("Draw::OnUpdate");
			Renderer2D::BeginScene(cameraController.GetCamera());

			Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 1.0f, 1.5f }, { 0.2f, 0.2f, 0.8f, 1.0f });
			Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, checkerTexture);

			Renderer2D::EndScene();
		}
	}
	
	void Sandbox2D::OnImGuiRender()
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));

		for (auto& result : profileResults)
		{
			char label[50];
			strcpy(label, "%.3fms ");
			strcat(label, result.name);
			ImGui::Text(label, result.time);
		}

		profileResults.clear();

		ImGui::End();
	}

	void Sandbox2D::OnEvent(Event& event)
	{
		cameraController.OnEvent(event);
	}


}