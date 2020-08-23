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
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		registry registry;
		uint32_t viewportWidth = 0, viewportHeight = 0;

		friend class Entity;
	};
}