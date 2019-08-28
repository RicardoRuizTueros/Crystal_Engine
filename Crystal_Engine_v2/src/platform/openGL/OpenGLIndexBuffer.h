#pragma once

#include "Crystal/renderer/IndexBuffer.h"

namespace Crystal
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return count; }
	private:
		uint32_t rendererID;
		uint32_t count;
	};
}