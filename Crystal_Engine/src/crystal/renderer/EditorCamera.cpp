#include "crystalpch.h"
#include "crystal/renderer/EditorCamera.h"

#include "crystal/core/Input.h"
#include "crystal/core/KeyCodes.h"
#include "crystal/core/MouseCodes.h"

#include <glfw/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Crystal {

	EditorCamera::EditorCamera(float fieldOfView, float aspectRatio, float nearClip, float farClip)
		: fieldOfView(fieldOfView), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip), Camera(perspective(radians(fieldOfView), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}

	void EditorCamera::UpdateProjection()
	{
		aspectRatio = viewportWidth / viewportHeight;
		projection = perspective(radians(fieldOfView), aspectRatio, nearClip, farClip);
	}

	void EditorCamera::UpdateView()
	{
		// m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation
		position = CalculatePosition();

		quat orientation = GetOrientation();
		view = translate(mat4(1.0f), position) * toMat4(orientation);
		view = inverse(view);
	}

	pair<float, float> EditorCamera::PanSpeed() const
	{
		// Values from cuadratic function plotted
		float x = std::min(viewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(viewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = this->distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			const vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			vec2 delta = (mouse - initialMousePosition) * 0.003f;
			initialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	void EditorCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(CRYSTAL_BIND_EVENT_FUNCTION(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& event)
	{
		float delta = event.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();

		return false;
	}

	void EditorCamera::MousePan(const vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		focalPoint += -GetRightDirection() * delta.x * xSpeed * distance;
		focalPoint += GetUpDirection() * delta.y * ySpeed * distance;
	}

	void EditorCamera::MouseRotate(const vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		yaw += yawSign * delta.x * RotationSpeed();
		pitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float delta)
	{
		distance -= delta * ZoomSpeed();
		if (distance < 1.0f)
		{
			focalPoint += GetForwardDirection();
			distance = 1.0f;
		}
	}

	vec3 EditorCamera::GetUpDirection() const
	{
		return rotate(GetOrientation(), vec3(0.0f, 1.0f, 0.0f));
	}

	vec3 EditorCamera::GetRightDirection() const
	{
		return rotate(GetOrientation(), vec3(1.0f, 0.0f, 0.0f));
	}

	vec3 EditorCamera::GetForwardDirection() const
	{
		return rotate(GetOrientation(), vec3(0.0f, 0.0f, -1.0f));
	}

	vec3 EditorCamera::CalculatePosition() const
	{
		return focalPoint - GetForwardDirection() * distance;
	}

	quat EditorCamera::GetOrientation() const
	{
		return quat(vec3(-pitch, -yaw, 0.0f));
	}
}
