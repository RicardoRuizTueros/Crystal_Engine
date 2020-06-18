#pragma once

#include "crystal/renderer/FrameBuffer.h"

namespace Crystal
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& specification);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return specification; }

	private:
		uint32_t rendererID, colorAttachment, depthAttachment;
		FrameBufferSpecification specification;
	};
}
