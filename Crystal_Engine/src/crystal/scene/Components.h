#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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
		vec3 translation = { 0.0f, 0.0f, 0.0f };
		vec3 rotation = { 0.0f, 0.0f, 0.0f };
		vec3 scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const vec3& translation)
			: translation(translation) {}

		mat4 GetTransform()
		{
			return
				translate(mat4(1.0f), translation) *
				toMat4(quat(rotation)) *
				glm::scale(mat4(1.0f), scale);
		}
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
