#include "crystalpch.h"
#include "OpenGLTexture2D.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Crystal
{
	OpenGLTexture2D::OpenGLTexture2D(const string& path) : path(path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		CRYSTAL_CORE_ASSERT(data, "Failed to load texture!");

		this->height = height;
		this->width = width;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, GL_RGB8, width, height);
		
		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, GL_RGB8, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererID);
	}

}
