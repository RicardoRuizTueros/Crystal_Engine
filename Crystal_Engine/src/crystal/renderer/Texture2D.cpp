#include "Texture2D.h"
#include <crystalpch.h>

#include "Renderer.h"
#include <platform/openGL/OpenGLTexture2D.h>

namespace Crystal
{
	Reference<Texture2D> Texture2D::Create(const string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return make_shared<OpenGLTexture2D>(path);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RenderAPI!");

		return nullptr;
	}
}