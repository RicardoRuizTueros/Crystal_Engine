#pragma once

#include "entt.hpp"
#include "crystal/core/Timestep.h"

using namespace entt;

namespace Crystal 
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entity CreateEntity();

		// To do: Remove this!
		registry& Registry() { return registry; }

		void OnUpdate(Timestep timestep);
	private:
		registry registry;
	};

}