#include "SceneHierarchyPanel.h"

#include "crystal/scene/Components.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
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
	
	static void DrawVec3Control(const string& label, vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
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
				auto& transformComponent = entity.GetComponent<TransformComponent>();

				DrawVec3Control("Translation", transformComponent.translation);
				
				vec3 rotation = degrees(transformComponent.rotation);
				DrawVec3Control("Rotation", rotation);
				transformComponent.rotation = radians(rotation);

				DrawVec3Control("Scale", transformComponent.scale);

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


		if (entity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
			{
				auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();

				ImGui::ColorEdit4("Color", value_ptr(spriteRendererComponent.color));
				ImGui::TreePop();
			}
		}
	}
}
