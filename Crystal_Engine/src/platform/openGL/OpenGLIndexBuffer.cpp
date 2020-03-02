#include "crystalpch.h"
#include "platform/openGL/OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Crystal 
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : count(count)
	{
		CRYSTAL_PROFILE_FUNCTION();

		glGenBuffers(1, &rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		CRYSTAL_PROFILE_FUNCTION();

		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
