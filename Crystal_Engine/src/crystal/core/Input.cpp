#include "crystalpch.h"
#include "crystal/core/Input.h"

#ifdef CRYSTAL_PLATFORM_WINDOWS
	#include "platform/windows/WindowsInput.h"
#endif

namespace Crystal
{
	Scope<Input> Input::instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef CRYSTAL_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		CRYSTAL_CORE_ASSERT(false, "Unknown platform");
		return nullptr;
#endif
	}
}