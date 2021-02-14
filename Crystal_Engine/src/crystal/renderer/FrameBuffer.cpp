#include "crystalpch.h"

#include "crystal/renderer/FrameBuffer.h"
#include "crystal/renderer/Renderer.h"

#include "platform/openGL/OpenGLFrameBuffer.h"

namespace Crystal
{
	Reference<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLFrameBuffer>(specification);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

