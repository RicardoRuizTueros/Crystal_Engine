#include "crystalpch.h"
#include "ContentBrowserPanel.h"

#include "imgui/imgui.h"

using namespace std;

namespace Crystal
{
	// To do: Change assets directory
	static const filesystem::path assetsPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel() : currentDirectory(assetsPath)
	{
		
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

		for (auto& directoryEntry : filesystem::directory_iterator(currentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = filesystem::relative(path, assetsPath);

			string filename = relativePath.filename().string();
			
			if (directoryEntry.is_directory())
			{
				if (ImGui::Button(filename.c_str()))
				{
					currentDirectory /= path.filename();
				}
			}
			else
			{
				if (ImGui::Button(filename.c_str()))
				{
				}
			}
		}

		ImGui::End();
	}
}
