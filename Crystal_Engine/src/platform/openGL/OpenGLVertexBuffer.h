#pragma once

#include "crystal/renderer/VertexBuffer.h"
#include "crystal/renderer/BufferLayout.h"

namespace Crystal
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override;
		virtual void SetLayout(const BufferLayout& layout) override;
	private:
		uint32_t rendererID;
		BufferLayout layout;
	};
}