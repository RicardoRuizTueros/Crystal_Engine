#pragma once

#include "crystal/renderer/OrthographicCamera.h"
#include "crystal/core/Timestep.h"
#include "crystal/events/ApplicationEvent.h"
#include "crystal/events/MouseEvent.h"
#include "crystal/core/KeyCodes.h"
#include "crystal/core/Input.h"

namespace Crystal
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool enableRotation = false);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }

		float GetZoomLevel() const { return zoomLevel; }
		void SetZoomLevel(float level) { zoomLevel = level; }
	private:
		float aspectRatio;
		float zoomLevel = 1.0f;
		bool enableRotation;
		vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
		float cameraRotation = 0.0f;
		float cameraTranslationSpeed = 5.0f;
		float cameraRotationSpeed = 180.0f;

		OrthographicCamera camera;

		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);

	};
}
