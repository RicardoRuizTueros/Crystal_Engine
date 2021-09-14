#pragma once

#include <filesystem>

using namespace std;

namespace Crystal
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		
		void OnImGuiRender();

	private:
		filesystem::path currentDirectory;
	};
}
