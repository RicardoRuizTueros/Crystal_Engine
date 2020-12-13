#pragma once

#include "crystal/renderer/Camera.h"
#include "crystal/core/Timestep.h"
#include "crystal/events/Event.h"
#include "crystal/events/MouseEvent.h"

#include <glm/glm.hpp>

using namespace glm;

namespace Crystal {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fieldOfView, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		inline float GetDistance() const { return distance; }
		inline void SetDistance(float distance) { distance = distance; }

		inline void SetViewportSize(float width, float height) { viewportWidth = width; viewportHeight = height; UpdateProjection(); }

		const mat4& GetView() const { return view; }
		mat4 GetViewProjection() const { return projection * view; }

		vec3 GetUpDirection() const;
		vec3 GetRightDirection() const;
		vec3 GetForwardDirection() const;
		const vec3& GetPosition() const { return position; }
		quat GetOrientation() const;

		float GetPitch() const { return pitch; }
		float GetYaw() const { return yaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& event);

		void MousePan(const vec2& delta);
		void MouseRotate(const vec2& delta);
		void MouseZoom(float delta);

		vec3 CalculatePosition() const;

		pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		float fieldOfView = 45.0f, aspectRatio = 1.778f, nearClip = 0.1f, farClip = 1000.0f;

		mat4 view;
		vec3 position = { 0.0f, 0.0f, 0.0f };
		vec3 focalPoint = { 0.0f, 0.0f, 0.0f };

		vec2 initialMousePosition = { 0.0f, 0.0f };

		float distance = 10.0f;
		float pitch = 0.0f, yaw = 0.0f;

		float viewportWidth = 1280, viewportHeight = 720;
	};
}
