#pragma once

#include "crystal/renderer/IndexBuffer.h"

namespace Crystal
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return count; }
	private:
		uint32_t rendererID;
		uint32_t count;
	};
}