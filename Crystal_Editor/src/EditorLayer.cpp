#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#include "ImGuizmo/ImGuizmo.h"
#include "math/Math.h"

using namespace glm;

namespace Crystal
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), cameraController(1920.0f / 1080.0f)
	{

	}

	void EditorLayer::OnAttach()
	{
		CRYSTAL_PROFILE_FUNCTION();

		FrameBufferSpecification frameBufferSpecification;
		frameBufferSpecification.attachmentsSpecification = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::DefaultDepth };
		frameBufferSpecification.width = 1280;
		frameBufferSpecification.height = 720;
		frameBuffer = FrameBuffer::Create(frameBufferSpecification);

		activeScene = CreateReference<Scene>();

		auto commandLineArguments = Application::Get().GetCommandLineArguments();
		if (commandLineArguments.count > 1)
		{
			auto sceneFilepath = commandLineArguments[1];
			SceneSerializer serializer(activeScene);
			serializer.Deserialize(sceneFilepath);
		}

		editorCamera = EditorCamera(30.0f, 1778.0f, 0.1f, 1000.0f);

		// Camera controller class
		class CameraController : public ScriptableEntity
		{
		public:
			virtual void OnCreate() override
			{
				auto& translation = GetComponent<TransformComponent>().translation;
				translation.x = rand() % 10 - 5.0f;
			}

			virtual void OnDestroy() override
			{
			}

			virtual void OnUpdate(Timestep timestep) override
			{
				auto& translation = GetComponent<TransformComponent>().translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * timestep;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * timestep;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * timestep;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * timestep;
			}
		};

		sceneHierarchyPanel.SetContext(activeScene);
	}

	void EditorLayer::OnDetach()
	{
		CRYSTAL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		CRYSTAL_PROFILE_FUNCTION();

		// Resize
		if (FrameBufferSpecification specification = frameBuffer->GetSpecification();
			viewportSize.x > 0.0f && viewportSize.y > 0.0f &&
			(specification.width != viewportSize.x || specification.height != viewportSize.y))
		{
			frameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			cameraController.OnResize(viewportSize.x, viewportSize.y);
			editorCamera.SetViewportSize(viewportSize.x, viewportSize.y);
			activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}

		// Update
		if (viewportFocused)
			cameraController.OnUpdate(timestep);

		editorCamera.OnUpdate(timestep);

		// Render
		Renderer2D::ResetStatistics();
		frameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		// Clear entityID attachment to -1
		frameBuffer->ClearAttachment(1, -1);

		// Update scene
		activeScene->OnUpdateEditor(timestep, editorCamera);

		auto [mouseX, mouseY] = ImGui::GetMousePos();
		mouseX -= viewportBounds[0].x;
		mouseY -= viewportBounds[0].y;

		vec2 viewPortSize = viewportBounds[1] - viewportBounds[0];
		mouseY = viewPortSize.y - mouseY; // Invert Y axis to match textures coordinates
		
		int mouseXInt = (int)mouseX;
		int mouseYInt = (int)mouseY;

		if (mouseXInt >= 0 && mouseYInt >= 0 && mouseXInt < (int)viewportSize.x && mouseYInt < (int)viewportSize.y)
		{
			int pixelData = frameBuffer->ReadPixel(1, mouseX, mouseY);
			hoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, activeScene.get());
		}

		frameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		CRYSTAL_PROFILE_FUNCTION();

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

		ImGuiStyle& style = ImGui::GetStyle();
		float minimumWindowSizeX = style.WindowMinSize.x;

		// Set the minimun docked window width
		style.WindowMinSize.x = 370.0f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		// Reset to default for non-docked windows
		style.WindowMinSize.x = minimumWindowSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save as...", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Exit")) Crystal::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		sceneHierarchyPanel.OnImGuiRender();
		contentBrowserPanel.OnImGuiRender();

		ImGui::Begin("Statistics");

		string hoveredEntityName = "None";
		if (hoveredEntity)
			hoveredEntityName = hoveredEntity.GetComponent<TagComponent>().tag;

		ImGui::Text("Hovered entity: %s", hoveredEntityName.c_str());

		auto statistics = Crystal::Renderer2D::GetStatistics();
		ImGui::Text("Renderer2D Statistics:");
		ImGui::Text("Draw Calls: %d", statistics.drawCalls);
		ImGui::Text("Quads: %d", statistics.quadCount);
		ImGui::Text("Vertices: %d", statistics.GetVertexCount());
		ImGui::Text("Indices: %d", statistics.GetIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		
		auto viewPortMinimumRegion = ImGui::GetWindowContentRegionMin();
		auto viewPortMaximumRegion = ImGui::GetWindowContentRegionMax();
		auto viewPortOffset = ImGui::GetWindowPos();

		viewportBounds[0] = { viewPortMinimumRegion.x + viewPortOffset.x, viewPortMinimumRegion.y + viewPortOffset.y };
		viewportBounds[1] = { viewPortMaximumRegion.x + viewPortOffset.x, viewPortMaximumRegion.y + viewPortOffset.y };

		viewportFocused = ImGui::IsWindowFocused();
		viewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewportFocused && !viewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = frameBuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Gizmos
		Entity selectedEntity = sceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && gizmoType != -1)
		{
			ImGuizmo::SetRect(viewportBounds[0].x, viewportBounds[0].y, viewportBounds[1].x - viewportBounds[0].x, viewportBounds[1].y - viewportBounds[0].y);

			// Runtime camera from Entity
			//auto cameraEntity = activeScene->GetPrimaryCameraEntity();
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().camera;
			//const mat4& cameraProjection = camera.GetProjection();
			//mat4 cameraView = inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Editor camera
			const mat4& cameraProjection = editorCamera.GetProjection();
			mat4 cameraView = editorCamera.GetView();


			// Selected entity transform
			auto& transformComponent = selectedEntity.GetComponent<TransformComponent>();
			mat4 transform = transformComponent.GetTransform();

			// Snaping. 0.5m - Translation/Scale, 45º - Rotation
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = gizmoType == ImGuizmo::OPERATION::ROTATE ? 45.0f : 0.5f;
			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(
				value_ptr(cameraView),
				value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)gizmoType, ImGuizmo::LOCAL,
				value_ptr(transform), nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				// Apply rotations as delta to avoid Gimbal Lock
				vec3 deltaRotation = rotation - transformComponent.rotation;
				transformComponent.translation = translation;
				transformComponent.rotation += deltaRotation;
				transformComponent.scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		cameraController.OnEvent(event);
		editorCamera.OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(CRYSTAL_BIND_EVENT_FUNCTION(OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(CRYSTAL_BIND_EVENT_FUNCTION(OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		// Shortcuts
		if (event.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);

		switch (event.GetKeyCode())
		{
		case Key::N:
			if (control)
				NewScene();
			break;

		case Key::O:
			if (control)
				OpenScene();
			break;

		case Key::S:
			if (control && shift)
				SaveSceneAs();
			break;

		// Gizmos
		case Key::Q:
			if (!ImGuizmo::IsUsing())
				gizmoType = -1;
			break;

		case Key::W:
			if (!ImGuizmo::IsUsing())
				gizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;

		case Key::E:
			if (!ImGuizmo::IsUsing())
				gizmoType = ImGuizmo::OPERATION::ROTATE;
			break;

		case Key::R:
			if (!ImGuizmo::IsUsing())
				gizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event)
	{
		if (event.GetMouseButton() == Mouse::ButtonLeft)
		{
			if (viewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
				sceneHierarchyPanel.SetSelectedEntity(hoveredEntity);
		}

		return false;
	}

	void EditorLayer::NewScene()
	{
		activeScene = CreateReference<Scene>();
		activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		sceneHierarchyPanel.SetContext(activeScene);
	}

	void EditorLayer::OpenScene()
	{
		string filepath = FileDialogs::OpenFile("Crystal scene (*.scene)\0*.scene\0");

		if (!filepath.empty())
		{
			activeScene = CreateReference<Scene>();
			activeScene->OnViewportResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			sceneHierarchyPanel.SetContext(activeScene);

			SceneSerializer serializer(activeScene);
			serializer.Deserialize(filepath);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		string filepath = FileDialogs::SaveFile("Crystal scene (*.scene)\0*.scene\0");

		if (!filepath.empty())
		{
			SceneSerializer serializer(activeScene);
			serializer.Serialize(filepath);
		}
	}
}
