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
		auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.color);
		}
	}

}