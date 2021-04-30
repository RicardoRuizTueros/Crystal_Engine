#pragma once

#include "Crystal.h"
#include "panels/SceneHierarchyPanel.h"

#include "crystal/scene/SceneSerializer.h"
#include "crystal/utils/PlatformUtils.h"
#include "crystal/renderer/EditorCamera.h"

namespace Crystal
{
	class EditorLayer : public Layer
	{

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);


		void NewScene();
		void OpenScene();
		void SaveSceneAs();

		EditorCamera editorCamera;

		OrthographicCameraController cameraController;
		vec2 viewportSize = { 0.0f, 0.0f };
		vec2 viewportBounds[2];
		bool viewportFocused = false, viewportHovered = false;

		Reference<Scene> activeScene;
		Reference<FrameBuffer> frameBuffer;
		SceneHierarchyPanel sceneHierarchyPanel;
		int gizmoType = -1;

		Entity hoveredEntity;
	};
}
