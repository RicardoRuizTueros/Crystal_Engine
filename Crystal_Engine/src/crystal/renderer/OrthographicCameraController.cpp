#include "crystalpch.h"
#include "OrthographicCameraController.h"

namespace Crystal
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), enableRotation(enableRotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		if (Input::IsKeyPressed(CRYSTAL_KEY_A))
			cameraPosition.x -= cameraTranslationSpeed * timestep;
		else if (Input::IsKeyPressed(CRYSTAL_KEY_D))
			cameraPosition.x += cameraTranslationSpeed * timestep;

		if (Input::IsKeyPressed(CRYSTAL_KEY_S))
			cameraPosition.y -= cameraTranslationSpeed * timestep;
		else if (Input::IsKeyPressed(CRYSTAL_KEY_W))
			cameraPosition.y += cameraTranslationSpeed * timestep;

		if (enableRotation)
		{
			if (Input::IsKeyPressed(CRYSTAL_KEY_Q))
				cameraRotation += cameraRotationSpeed * timestep;
			else if (Input::IsKeyPressed(CRYSTAL_KEY_E))
				cameraRotation -= cameraRotationSpeed * timestep;

			camera.SetRotation(cameraRotation);
		}

		camera.SetPosition(cameraPosition);

		// Further -> Faster, Closer -> Slower
		cameraTranslationSpeed = zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(CRYSTAL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CRYSTAL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		zoomLevel -= event.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

}