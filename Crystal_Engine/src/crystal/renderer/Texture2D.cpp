#include "crystalpch.h"

#include "crystal/renderer/Texture2D.h"
#include "crystal/renderer/Renderer.h"

#include "platform/openGL/OpenGLTexture2D.h"

namespace Crystal
{
	Reference<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLTexture2D>(width, height);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RenderAPI!");

		return nullptr;
	}
	Reference<Texture2D> Texture2D::Create(const string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLTexture2D>(path);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RenderAPI!");

		return nullptr;
	}
}