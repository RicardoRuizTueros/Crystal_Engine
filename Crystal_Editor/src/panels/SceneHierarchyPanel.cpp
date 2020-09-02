#include "SceneHierarchyPanel.h"

#include "crystal/scene/Components.h"

#include <imgui/imgui.h>

namespace Crystal
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Reference<Scene>& scene)
	{
		SetContext(scene);
	}
	
	void SceneHierarchyPanel::SetContext(const Reference<Scene>& scene)
	{
		this->scene = scene;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene hierarchy");

		scene->registry.each([&](auto entityID)
		{
			Entity entity{ entityID, scene.get() };
			DrawEntityNode(entity);
		});

		ImGui::End();
	}
	
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		
		if (ImGui::IsItemClicked())
			selectedEntity = entity;
		
		if (selectedEntity == entity)
			flags |= ImGuiTreeNodeFlags_Selected;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (opened)
		{
			// Test
			bool opened = ImGui::TreeNodeEx((void*)987239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

	}
}
