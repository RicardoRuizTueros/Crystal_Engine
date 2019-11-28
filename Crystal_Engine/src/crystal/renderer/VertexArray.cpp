#include "crystalpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "platform/openGL/OpenGLVertexArray.h"

namespace Crystal
{
	Reference<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return make_shared<OpenGLVertexArray>();
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return 0;
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}