#pragma once

#include "crystal/scene/Entity.h"

namespace Crystal
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

		template<typename ComponentType>
		ComponentType& GetComponent()
		{
			return entity.GetComponent<ComponentType>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnDestroy() {}
	private:
		Entity entity;
		friend class Scene;
	};
}
