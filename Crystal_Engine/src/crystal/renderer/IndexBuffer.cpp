#pragma once

#include "crystalpch.h"

#include "crystal/renderer/IndexBuffer.h"
#include "crystal/renderer/Renderer.h"

#include "platform/openGL/OpenGLIndexBuffer.h"

namespace Crystal
{
	Reference<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLIndexBuffer>(indices, size);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}