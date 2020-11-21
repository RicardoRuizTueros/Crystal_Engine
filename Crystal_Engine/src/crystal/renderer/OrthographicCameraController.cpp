#include "crystalpch.h"

#include "crystal/renderer/OrthographicCameraController.h"

namespace Crystal
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), enableRotation(enableRotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		CRYSTAL_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Key::A)) 
		{
			cameraPosition.x -= cos(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
			cameraPosition.y -= sin(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			cameraPosition.x += cos(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
			cameraPosition.y += sin(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(Key::S))
		{
			cameraPosition.x -= -sin(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
			cameraPosition.y -= cos(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
		}
		else if (Input::IsKeyPressed(Key::W))
		{
			cameraPosition.x += -sin(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
			cameraPosition.y += cos(radians(cameraRotation)) * cameraTranslationSpeed * timestep;
		}

		if (enableRotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				cameraRotation += cameraRotationSpeed * timestep;
			else if (Input::IsKeyPressed(Key::E))
				cameraRotation -= cameraRotationSpeed * timestep;

			if (cameraRotation > 180.0f)
				cameraRotation -= 360.0f;
			else if (cameraRotation <= -180.0f)
				cameraRotation += 360.0f;

			camera.SetRotation(cameraRotation);
		}

		camera.SetPosition(cameraPosition);

		// Further -> Faster, Closer -> Slower
		cameraTranslationSpeed = zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		CRYSTAL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(CRYSTAL_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CRYSTAL_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		aspectRatio = width / height;
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		CRYSTAL_PROFILE_FUNCTION();

		zoomLevel -= event.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		CRYSTAL_PROFILE_FUNCTION();

		OnResize((float)event.GetWidth(), (float)event.GetHeight());
		return false;
	}

}
