#pragma once

#include <filesystem>
#include "crystal/renderer/Texture2D.h"

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

		Reference<Texture2D> directoryIcon;
		Reference<Texture2D> fileIcon;
	};
}
