#pragma once

#include "crystal/scene/Scene.h"
#include "entt.hpp"

using namespace entt;
using namespace std;

namespace Crystal
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entity entityHandler, Scene* scene);
		Entity(const Entity& entity) = default;
		
		template<typename ComponentType, typename... Arguments>
		ComponentType& AddComponent(Arguments&&... arguments)
		{
			CRYSTAL_CORE_ASSERT(!HasComponent<ComponentType>(), "Entity has already that component!");
			return scene->registry.emplace<ComponentType>(entityHandler, forward<Arguments>(arguments)...);
		}

		template<typename ComponentType>
		ComponentType& GetComponent()
		{
			CRYSTAL_CORE_ASSERT(HasComponent<ComponentType>(), "Entity does not have that component!");
			return scene->registry.get<ComponentType>(entityHandler);
		}

		template<typename ComponentType>
		bool HasComponent()
		{
			return scene->registry.has<ComponentType>(entityHandler);
		}

		template<typename ComponentType>
		void RemoveComponent()
		{
			CRYSTAL_CORE_ASSERT(HasComponent<ComponentType>(), "Entity does not have that component!");
			scene->registry.remove<ComponentType>(entityHandler);
		}

		operator bool() const { return entityHandler != entt::null; }
		operator uint32_t() const { return (uint32_t)entityHandler; }
		
		bool operator == (const Entity& other) const
		{
			return entityHandler == other.entityHandler && scene == other.scene;
		}
		
		bool operator != (const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entity entityHandler = { entt::null };
		Scene* scene = nullptr;

	};
}
