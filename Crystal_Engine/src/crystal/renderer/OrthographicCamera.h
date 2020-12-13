#pragma once
#include <glm/glm.hpp>

using namespace glm;

namespace Crystal
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		inline const vec3& GetPosition() const { return position; }
		void SetPosition(const vec3& position);
		
		inline float GetRotation() const { return rotation; }
		void SetRotation(float rotation);
		void SetProjection(float left, float right, float bottom, float top);
		inline const mat4& GetProjection() const { return projectionMatrix; }
		inline const mat4& GetView() const { return viewMatrix; }
		inline const mat4& GetViewProjection() const { return viewProjectionMatrix; }

	private:
		mat4 projectionMatrix;
		mat4 viewMatrix;
		mat4 viewProjectionMatrix;

		vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;

		void RecalculateViewMatrix();
	};
}
