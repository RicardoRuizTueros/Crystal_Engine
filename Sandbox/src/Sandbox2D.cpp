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
		CRYSTAL_PROFILE_FUNCTION();

		checkerTexture = Texture2D::Create("assets/textures/checkerboard.png");
	}

	void Sandbox2D::OnDetach()
	{
		CRYSTAL_PROFILE_FUNCTION();
	}

	void Sandbox2D::OnUpdate(Timestep timestep)
	{
		CRYSTAL_PROFILE_FUNCTION();

		cameraController.OnUpdate(timestep);

		Renderer2D::ResetStatistics();

		{
			CRYSTAL_PROFILE_SCOPE("RenderCommand::OnUpdate");
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();
		}

		{
			static float rotation = 0.0f;
			rotation += timestep * 50.0f;

			CRYSTAL_PROFILE_SCOPE("DrawQuad::OnUpdate");
			Renderer2D::BeginScene(cameraController.GetCamera());

			Renderer2D::DrawRotatedQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, -45, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ -2.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.5f }, { 0.2f, 0.2f, 0.8f, 1.0f });
			Renderer2D::DrawQuad({ -10.0f, -10.0f, -0.2f }, { 20.0f, 20.0f }, checkerTexture, 10.0f);

			Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, rotation, checkerTexture, 10.0f);

			Renderer2D::EndScene();

			Renderer2D::BeginScene(cameraController.GetCamera());
			
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					Renderer2D::DrawQuad({ x, y }, { 0.45, 0.45 }, color);
				}
			}

			Renderer2D::EndScene();
		}
	}

	void Sandbox2D::OnImGuiRender()
	{
		CRYSTAL_PROFILE_FUNCTION();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
		ImGui::End();

		auto statistics = Renderer2D::GetStatistics();
		ImGui::Begin("Renderer2D Statistics");
		ImGui::Text("Draw calls %d", statistics.drawCalls);
		ImGui::Text("Quads %d", statistics.quadCount);
		ImGui::Text("Vertices %d", statistics.GetVertexCount());
		ImGui::Text("Indices %d", statistics.GetIndexCount());
		ImGui::End();


	}

	void Sandbox2D::OnEvent(Event& event)
	{
		cameraController.OnEvent(event);
	}


}