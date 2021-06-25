#include "Crystal.h"
#include "crystal/core/EntryPoint.h"

#include "EditorLayer.h"

namespace Crystal
{
	class EditorApp : public Application
	{
	public:
		EditorApp::EditorApp(ApplicationCommandLineArguments arguments)
			: Application("Crystal Editor", arguments)
		{
			PushLayer(new EditorLayer());
		}
	
		EditorApp::~EditorApp()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArguments arguments)
	{
		return new EditorApp(arguments);
	}
}
