#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Crystal
{
	class Camera
	{
	public:
		Camera(const mat4& projection) : projection(projection) {}

		const mat4& GetProjection() const { return projection; }
	private:
		mat4 projection;
	};
}