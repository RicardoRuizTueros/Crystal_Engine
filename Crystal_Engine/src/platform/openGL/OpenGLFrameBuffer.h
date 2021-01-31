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

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
		{
			CRYSTAL_CORE_ASSERT(index < colorAttachments.size(), "Invalid index");
			return colorAttachments[index];
		}
		
		virtual const FrameBufferSpecification& GetSpecification() const override { return frameBufferSpecification; }

	private:
		uint32_t rendererID = 0, colorAttachment = 0, depthAttachment = 0;
		FrameBufferSpecification frameBufferSpecification;

		vector<FrameBufferTextureSpecification> colorAttachmentSpecifications;
		FrameBufferTextureSpecification depthAttachmentSpecification = FrameBufferTextureFormat::None;

		vector<uint32_t> colorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}
