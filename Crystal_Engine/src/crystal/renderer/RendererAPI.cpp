#include "crystalpch.h"

#include "crystal/renderer/RendererAPI.h"

#include "platform/openGL/OpenGLRendererAPI.h"

namespace Crystal
{
	RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (api)
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}