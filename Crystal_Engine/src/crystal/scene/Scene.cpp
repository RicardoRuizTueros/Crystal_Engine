#include "crystalpch.h"

#include "crystal/scene/Scene.h"
#include "crystal/renderer/Renderer2D.h"
#include "crystal/scene/Entity.h"

#include "crystal/scene/Components.h"

#include <glm/glm.hpp>

namespace Crystal
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const string& name)
	{
		Entity entity = { registry.create(), this };
		entity.AddComponent<TransformComponent>();

		TagComponent tagComponent;

		if (name.empty())
			tagComponent = entity.AddComponent<TagComponent>("Entity");
		else
			tagComponent = entity.AddComponent<TagComponent>(name);

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		Camera* mainCamera = nullptr;
		mat4* mainCameraTransform = nullptr;

		// Scripts
		{
			registry.view<NativeScriptComponent>().each([=](auto entity, auto& nativeScriptComponent)
				{
					if (!nativeScriptComponent.instance)
					{
						nativeScriptComponent.instance = nativeScriptComponent.InstantiateScript();
						nativeScriptComponent.instance->entity = Entity{ entity, this };
						nativeScriptComponent.instance->OnCreate();
					}

					nativeScriptComponent.instance->OnUpdate(timestep);
				}
			);
		}


		// Cameras
		{
			auto view = registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transformComponent, cameraComponent] = view.get<TransformComponent, CameraComponent>(entity);

				if (cameraComponent.primary)
				{

					mainCamera = &cameraComponent.camera;
					mainCameraTransform = &transformComponent.GetTransform();
					break;
				}
			}
		}


		// Sprite rendering
		{
			if (mainCamera)
			{
				Renderer2D::BeginScene(mainCamera->GetProjection(), *mainCameraTransform);

				auto group = registry.group<TransformComponent, SpriteRendererComponent>();
				for (auto entity : group)
				{
					auto [transformComponent, spriteComponent] = group.get<TransformComponent, SpriteRendererComponent>(entity);
					Renderer2D::DrawQuad(transformComponent.GetTransform(), spriteComponent.color);
				}

				Renderer2D::EndScene();
			}
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		viewportWidth = width;
		viewportHeight = height;

		auto view = registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.fixedAspectRatio)
				cameraComponent.camera.SetViewportSize(width, height);
		}
	}

	template<typename ComponentType>
	void Scene::OnComponentAdded(Entity entity, ComponentType& component)
	{
		// Generic template should never be called!
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
		
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		// Updates viewport to render the new camera
		component.camera.SetViewportSize(viewportWidth, viewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}

}
