#include "crystalpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Crystal
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}
	
	void SceneCamera::SetOrthographic(float height, float nearClip, float farClip)
	{
		orthographicHeight = height;
		orthographicNear = nearClip;
		orthographicFar = farClip;

		RecalculateProjection();
	}
	
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		aspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}
	
	void SceneCamera::RecalculateProjection()
	{
		float orthographicLeft = -orthographicHeight * aspectRatio * 0.5f;
		float orthographicRight = orthographicHeight * aspectRatio * 0.5f;
		float orthographicBottom = -orthographicHeight * 0.5f;
		float orthographicTop = orthographicHeight * 0.5f;

		projection = ortho(orthographicLeft, orthographicRight, orthographicBottom, 
			orthographicTop, orthographicNear, orthographicFar);
	}
}