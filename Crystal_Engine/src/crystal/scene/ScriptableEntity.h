#pragma once

#include "crystal/scene/Entity.h"

namespace Crystal
{
	class ScriptableEntity
	{
	public:
		template<typename ComponentType>
		ComponentType& GetComponent()
		{
			return entity.GetComponent<ComponentType>();
		}
	private:
		Entity entity;
		friend class Scene;
	};
}