#pragma once

#include "crystalpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "platform/openGL/OpenGLIndexBuffer.h"

namespace Crystal
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}