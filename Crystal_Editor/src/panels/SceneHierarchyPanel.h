#pragma once

#include "crystal/core/Base.h"

#include "crystal/scene/Scene.h"
#include "crystal/scene/Entity.h"

namespace Crystal
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Reference<Scene>& scene);
		
		void SetContext(const Reference<Scene>& scene);

		void OnImGuiRender();

		Entity const GetSelectedEntity() { return selectedEntity; }
		void SetSelectedEntity(Entity entity);
	private:
		Reference<Scene> scene;
		Entity selectedEntity;

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	};
}
