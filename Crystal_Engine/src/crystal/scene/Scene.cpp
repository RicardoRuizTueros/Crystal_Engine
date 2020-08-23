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

	void Scene::OnUpdate(Timestep timestep)
	{
		Camera* mainCamera = nullptr;
		mat4* mainCameraTransform = nullptr;

		auto view = registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& [transformComponent, cameraComponent] = view.get<TransformComponent, CameraComponent>(entity);

			if (cameraComponent.primary)
			{
				mainCamera = &cameraComponent.camera;
				mainCameraTransform = &transformComponent.transform;
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *mainCameraTransform);

			auto group = registry.group<TransformComponent, SpriteRendererComponent>();
			for (auto entity : group)
			{
				auto& [transformComponent, spriteComponent] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transformComponent, spriteComponent.color);
			}

			Renderer2D::EndScene();
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

}