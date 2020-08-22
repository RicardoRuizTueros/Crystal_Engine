#pragma once

#include <glm/glm.hpp>

#include "crystal/renderer/Camera.h"

using namespace glm;
using namespace std;

namespace Crystal 
{
	struct TagComponent
	{
		string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const string& tag) 
			: tag(tag) {};
	};

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

	struct CameraComponent
	{
		Camera camera;
		bool primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const mat4& projection)
			: camera(projection) {}
	};
}
