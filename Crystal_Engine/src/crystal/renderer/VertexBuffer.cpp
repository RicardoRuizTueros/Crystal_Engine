#pragma once

#include "crystalpch.h"
#include "VertexBuffer.h"

#include "Renderer.h"

#include "platform/openGL/OpenGLVertexBuffer.h"

namespace Crystal 
{
	VertexBuffer* Crystal::VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}