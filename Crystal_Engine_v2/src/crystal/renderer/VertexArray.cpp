#include "crystalpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "platform/openGL/OpenGLVertexArray.h"

namespace Crystal
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		case RendererAPI::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return 0;
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}