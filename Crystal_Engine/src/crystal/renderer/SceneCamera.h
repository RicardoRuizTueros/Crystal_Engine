#pragma once

#include "crystal/renderer/Camera.h"

namespace Crystal
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

		SceneCamera();
		virtual ~SceneCamera() = default;
		
		void SetViewportSize(uint32_t width, uint32_t height);
		
		void SetPerspective(float fieldOfView, float nearClip, float farClip);
		void SetOrthographic(float height, float nearClip, float farClip);

		float GetPerspectiveVerticalFieldOfView() const { return perspectiveVerticalFieldOfView; }
		void SetPerspeciveVerticalFieldOfView(float fieldOfViewVertical) 
		{
			perspectiveVerticalFieldOfView = fieldOfViewVertical; 
			RecalculateProjection();
		}

		float GetPerspectiveNearClip() const { return perspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) 
		{
			perspectiveNear = nearClip; 
			RecalculateProjection();
		}

		float GetPerspectiveFarClip() const { return perspectiveFar; }
		void SetPerspectiveFarClip(float farClip) 
		{
			perspectiveFar = farClip; 
			RecalculateProjection();
		}

		float GetOrthographicNearClip() const { return orthographicNear; }
		void SetOrthographicNearClip(float nearClip)
		{
			orthographicNear = nearClip;
			RecalculateProjection();
		}
		
		float GetOrthographicFarClip() const { return orthographicFar; }
		void SetOrthographicFarClip(float farClip)
		{
			orthographicFar = farClip; 
			RecalculateProjection();
		}

		ProjectionType GetProjectionType() const { return projectionType; }
		void SetProjectionType(ProjectionType type) 
		{
			projectionType = type; 
			RecalculateProjection();
		}

		float GetOrthographicSize() const { return orthographicHeight; }
		void SetOrthographicSize(float height) 
		{
			orthographicHeight = height; 
			RecalculateProjection();
		}

	private:
		ProjectionType projectionType = ProjectionType::Perspective;

		float perspectiveVerticalFieldOfView = radians(45.0f);
		float perspectiveNear = 0.01f, perspectiveFar = 1000.0f;

		float orthographicHeight = 10.0f;
		float orthographicNear = -1.0f, orthographicFar = 1.0f;
		float aspectRatio = 0.0f;

		void RecalculateProjection();
	};
}
