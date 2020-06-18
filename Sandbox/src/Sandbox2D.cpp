#include "Sandbox2D.h"

#include "platform/openGL/OpenGLShader.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

using namespace glm;
using namespace Crystal;

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1920.0f / 1080.0f), squareColor({ 0.2f, 0.8f, 0.3f, 1.0f })
{

}

void Sandbox2D::OnAttach()
{
	CRYSTAL_PROFILE_FUNCTION();

	checkerTexture = Texture2D::Create("assets/textures/checkerboard.png");

	FrameBufferSpecification frameBufferSpecification;
	frameBufferSpecification.width = 1280;
	frameBufferSpecification.height = 720;
	frameBuffer = FrameBuffer::Create(frameBufferSpecification);
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
		frameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += timestep * 50.0f;

		CRYSTAL_PROFILE_SCOPE("DrawQuad::OnUpdate");
		Renderer2D::BeginScene(cameraController.GetCamera());

		Renderer2D::DrawRotatedQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, -45, squareColor);
		Renderer2D::DrawQuad({ -2.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.5f }, { 0.2f, 0.2f, 0.8f, 1.0f });
		Renderer2D::DrawQuad({ -10.0f, -10.0f, -0.2f }, { 20.0f, 20.0f }, checkerTexture, 10.0f);

		Renderer2D::DrawRotatedQuad({ 15.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, rotation, checkerTexture, 10.0f);

		Renderer2D::EndScene();
		frameBuffer->Unbind();

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

	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Crystal::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto statistics = Crystal::Renderer2D::GetStatistics();
		ImGui::Text("Renderer2D Statistics:");
		ImGui::Text("Draw Calls: %d", statistics.drawCalls);
		ImGui::Text("Quads: %d", statistics.quadCount);
		ImGui::Text("Vertices: %d", statistics.GetVertexCount());
		ImGui::Text("Indices: %d", statistics.GetIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));

		uint32_t textureID = frameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");

		auto statistics = Crystal::Renderer2D::GetStatistics();
		ImGui::Text("Renderer2D Statistics:");
		ImGui::Text("Draw Calls: %d", statistics.drawCalls);
		ImGui::Text("Quads: %d", statistics.quadCount);
		ImGui::Text("Vertices: %d", statistics.GetVertexCount());
		ImGui::Text("Indices: %d", statistics.GetIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));

		uint32_t textureID = checkerTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Event& event)
{
	cameraController.OnEvent(event);
}