#include "crystalpch.h"
#include "UniformBuffer.h"

#include "crystal/renderer/Renderer.h"
#include "platform/openGL/OpenGLUniformBuffer.h"

namespace Crystal
{
	Reference<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLUniformBuffer>(size, binding);
		}
		
		CRYSTAL_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}
