#include "SceneHierarchyPanel.h"

#include "crystal/scene/Components.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectedEntity = {};

		ImGui::End();

		ImGui::Begin("Properties");

		if (selectedEntity)
			DrawComponents(selectedEntity);

		ImGui::End();

	}
	
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

		if (selectedEntity == entity)
			flags |= ImGuiTreeNodeFlags_Selected;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
			selectedEntity = entity;
		
		if (opened)
		{
			flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			
			if (opened)
				ImGui::TreePop();
			
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());

			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
				tag = string(buffer);
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().transform;

				ImGui::DragFloat3("Position", value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.camera;

				ImGui::Checkbox("Primary", &cameraComponent.primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int type = 0; type < 2; type++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[type];

						if (ImGui::Selectable(projectionTypeStrings[type], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[type];
							camera.SetProjectionType((SceneCamera::ProjectionType) type);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float verticalFieldOfView = degrees(camera.GetPerspectiveVerticalFieldOfView());
					if (ImGui::DragFloat("Field of view", &verticalFieldOfView))
						camera.SetPerspeciveVerticalFieldOfView(radians(verticalFieldOfView));

					float perspectiveNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNearClip(perspectiveNear);
					
					float perspectiveFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFarClip(perspectiveFar);
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthographicSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthographicSize))
						camera.SetOrthographicSize(orthographicSize);

					float orthographicNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthographicNear))
						camera.SetOrthographicNearClip(orthographicNear);

					float orthographicFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthographicFar))
						camera.SetOrthographicFarClip(orthographicFar);
				
					ImGui::Checkbox("Fixed aspect ratio", &cameraComponent.fixedAspectRatio);
				}


				ImGui::TreePop();
			}
		}
	}
}
