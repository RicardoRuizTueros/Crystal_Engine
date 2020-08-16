#include "crystalpch.h"
#include "crystal/scene/Scene.h"

#include "crystal/scene/Components.h"
#include "crystal/renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Crystal 
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	entity Scene::CreateEntity()
	{
		return registry.create();
	}

	void Scene::OnUpdate(Timestep timestep)
	{
		auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.color);
		}


	}

}