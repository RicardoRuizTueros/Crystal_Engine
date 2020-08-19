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

		void OnUpdate(Timestep timestep);
	private:
		registry registry;
		
		friend class Entity;
	};
}