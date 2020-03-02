#include "crystalpch.h"
#include "platform/openGL/OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Crystal
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		CRYSTAL_PROFILE_FUNCTION();

		glGenBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		CRYSTAL_PROFILE_FUNCTION();

		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return layout;
	}
	
	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		this->layout = layout;
	}
}
