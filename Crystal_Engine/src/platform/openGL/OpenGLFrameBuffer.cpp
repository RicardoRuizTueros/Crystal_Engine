#include "crystalpch.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Crystal
{
	static const uint32_t maxFrameBufferSize = 8192;

	// Todo: Move this to utils
	namespace Utils
	{
		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;

			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDephTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;

			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FrameBufferTextureFormat format)
		{
			switch (format)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				return true;
			}

			return false;
		}
	}


	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& specification)
		:frameBufferSpecification(specification)
	{
		for (auto specification : specification.attachmentsSpecification.attachments)
		{
			if (Utils::IsDepthFormat(specification.format))
				depthAttachmentSpecification = specification;
			else
				colorAttachmentSpecifications.emplace_back(specification);
		}

		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &rendererID);
		glDeleteTextures(colorAttachments.size(), colorAttachments.data());
		glDeleteTextures(1, &depthAttachment);
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (rendererID)
		{
			glDeleteFramebuffers(1, &rendererID);
			glDeleteTextures(colorAttachments.size(), colorAttachments.data());
			glDeleteTextures(1, &depthAttachment);

			colorAttachments.clear();
			depthAttachment = 0;
		}

		glCreateFramebuffers(1, &rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

		bool multisampled = frameBufferSpecification.samples > 1;

		// Attachments

		if (colorAttachmentSpecifications.size())
		{
			colorAttachments.resize(colorAttachmentSpecifications.size());
			Utils::CreateTextures(multisampled, colorAttachments.data(), colorAttachments.size());

			for (size_t index = 0; index < colorAttachments.size(); index++)
			{
				Utils::BindTexture(multisampled, colorAttachments[index]);

				switch (colorAttachmentSpecifications[index].format)
				{
				case FrameBufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(colorAttachments[index], frameBufferSpecification.samples, GL_RGBA8,
						frameBufferSpecification.width, frameBufferSpecification.height, index);
					break;
				}
			}
		}

		if (depthAttachmentSpecification.format != FrameBufferTextureFormat::None)
		{
			Utils::CreateTextures(multisampled, &depthAttachment, 1);
			Utils::BindTexture(multisampled, depthAttachment);

			switch (depthAttachmentSpecification.format)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				Utils::AttachDephTexture(depthAttachment, frameBufferSpecification.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
					frameBufferSpecification.width, frameBufferSpecification.height);
				break;
			}
		}

		if (colorAttachments.size() > 1)
		{
			CRYSTAL_CORE_ASSERT(colorAttachments.size() < 4, "Only 4 color attachments supported!");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(colorAttachments.size(), buffers);
		}
		else if (colorAttachments.empty())
		{
			// Depth-only pass
			glDrawBuffer(GL_NONE);
		}

		CRYSTAL_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > maxFrameBufferSize || height > maxFrameBufferSize)
		{
			CRYSTAL_CORE_WARNING("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}

		frameBufferSpecification.width = width;
		frameBufferSpecification.height = height;

		Invalidate();
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
		glViewport(0, 0, frameBufferSpecification.width, frameBufferSpecification.height);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
