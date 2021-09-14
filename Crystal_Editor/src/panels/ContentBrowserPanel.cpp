#include "crystalpch.h"
#include "ContentBrowserPanel.h"

#include "imgui/imgui.h"

using namespace std;

namespace Crystal
{
	// To do: Change assets directory
	static const filesystem::path assetsPath = "assets";

	static float padding = 16.0f;
	static float thumbnailSize = 128.0f;
	float cellSize = thumbnailSize + padding;

	ContentBrowserPanel::ContentBrowserPanel() : currentDirectory(assetsPath)
	{
		directoryIcon = Texture2D::Create("resources/icons/ContentBrowser/DirectoryIcon.png");
		fileIcon = Texture2D::Create("resources/icons/ContentBrowser/FileIcon.png");
	}
	
	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (currentDirectory != filesystem::path(assetsPath))
		{
			if (ImGui::Button("<-"))
			{
				currentDirectory = currentDirectory.parent_path();
			}
		}

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : filesystem::directory_iterator(currentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = filesystem::relative(path, assetsPath);

			string filename = relativePath.filename().string();
			Reference<Texture2D> icon = directoryEntry.is_directory() ? directoryIcon : fileIcon;

			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
				{
					currentDirectory /= path.filename();
				}
			}

			ImGui::TextWrapped(filename.c_str());
			ImGui::NextColumn();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		// To do: status bar

		ImGui::End();
	}
}
