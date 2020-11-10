#include "Crystal.h"
#include "crystal/core/EntryPoint.h"

#include "EditorLayer.h"

namespace Crystal
{
	class EditorApp : public Application
	{
	public:
		EditorApp::EditorApp()
			: Application("Crystal Editor")
		{
			PushLayer(new EditorLayer());
		}
	
		EditorApp::~EditorApp()
		{

		}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}
