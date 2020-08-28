#pragma once

#include <glm/glm.hpp>

#include "crystal/renderer/SceneCamera.h"
#include "crystal/scene/ScriptableEntity.h"

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
		SceneCamera camera;
		bool primary = true;
		bool fixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename InstanceType>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new InstanceType()); };
			DestroyScript = [](NativeScriptComponent* nativeScriptComponent)
			{
				delete nativeScriptComponent->instance;
				nativeScriptComponent->instance = nullptr;
			};
		}
	};
}
