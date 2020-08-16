#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Crystal 
{
	struct TransformComponent
	{
		mat4 transform = mat4{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const mat4& transform)
			: transform(transform) {}

		operator mat4& () { return transform; }
		operator const mat4& () const { return transform; }
	};

	struct SpriteRendererComponent
	{
		vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const vec4& color)
			: color(color) {}
	};
}
