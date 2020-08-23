#pragma once

#include "crystal/renderer/Camera.h"

namespace Crystal
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float height, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthographicHeight() const { return orthographicHeight; }
		void SetOrthographicSize(float height) { orthographicHeight = height; RecalculateProjection(); }

	private:
		float orthographicHeight = 10.0f;
		float orthographicNear = -1.0f, orthographicFar = 1.0f;
		float aspectRatio = 0.0f;

		void RecalculateProjection();
	};
}
