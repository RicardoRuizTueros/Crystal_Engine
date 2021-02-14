#pragma once

#include "Crystal/Core/Base.h"

namespace Crystal
{
	enum class FrameBufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER, // Used for mouse picking an Entity ID

		// Deph/Stencil
		DEPTH24STENCIL8,

		// Defaults
		DefaultDepth = DEPTH24STENCIL8
	};
	
	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureFormat format = FrameBufferTextureFormat::None;

		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format) : format(format) {};

		// Todo: filtering/wrap
	};

	struct FrameBufferAttachmentSpecification
	{
		vector<FrameBufferTextureSpecification> attachments;

		FrameBufferAttachmentSpecification() = default;
		FrameBufferAttachmentSpecification(initializer_list<FrameBufferTextureSpecification> attachments)
			: attachments(attachments) {};
	};

	struct FrameBufferSpecification
	{
		FrameBufferAttachmentSpecification attachmentsSpecification;

		uint32_t width = 0, height = 0;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
	
		static Reference<FrameBuffer> Create(const FrameBufferSpecification& specification);
	};
}
