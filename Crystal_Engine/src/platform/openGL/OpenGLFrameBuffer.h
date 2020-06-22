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
		
		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return specification; }

	private:
		uint32_t rendererID = 0, colorAttachment = 0, depthAttachment = 0;
		FrameBufferSpecification specification;
	};
}
