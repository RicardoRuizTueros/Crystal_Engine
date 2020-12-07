#pragma once

#include "entt.hpp"
#include "crystal/core/Timestep.h"

using namespace entt;

namespace Crystal 
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const string& name = string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep timestep);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();
	private:
		registry registry;
		uint32_t viewportWidth = 1, viewportHeight = 1;

		template <typename ComponentType>
		void OnComponentAdded(Entity entity, ComponentType& component);

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
	};
}
