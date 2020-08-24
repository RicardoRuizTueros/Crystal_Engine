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

		function<void()> InstantiateFunction;
		function<void()> DestroyFunction;

		function<void(ScriptableEntity*)> OnCreateFunction;
		function<void(ScriptableEntity*)> OnDestroyFunction;
		function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;

		template<typename InstanceType>
		void Bind()
		{
			InstantiateFunction = [&]() {instance = new InstanceType(); };
			DestroyFunction = [&]() {delete (InstanceType*)instance; instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* instance) {((InstanceType*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) {((InstanceType*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep timestep) {((InstanceType*)instance)->OnUpdate(timestep); };

		}
	};
}
