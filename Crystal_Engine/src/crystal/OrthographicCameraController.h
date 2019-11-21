#pragma once

#include <crystal\renderer\OrthographicCamera.h>
#include <crystal\core\Timestep.h>
#include <crystal\events\ApplicationEvent.h>
#include <crystal\events\MouseEvent.h>
#include <crystal\KeyCodes.h>
#include <crystal\Input.h>

namespace Crystal
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRation, bool enableRotation = false);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }
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