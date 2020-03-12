#include "crystalpch.h"
#include "crystal/core/Window.h"

#ifdef CRYSTAL_PLATFORM_WINDOWS
#include "platform/windows/WindowsWindow.h"
#endif

namespace Crystal
{
	Scope<Window> Window::Create(const WindowProperties& properties)
	{
#ifdef CRYSTAL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(properties);
#else
		CRYSTAL_CORE_ASSERT(false, "Unknown platform!")
			return nullptr;
#endif
	}
}