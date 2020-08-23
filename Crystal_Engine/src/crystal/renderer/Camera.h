#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Crystal
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const mat4& projection) : projection(projection) {}
		virtual ~Camera() = default;

		const mat4& GetProjection() const { return projection; }
	protected:
		mat4 projection = mat4(1.0f);
	};
}