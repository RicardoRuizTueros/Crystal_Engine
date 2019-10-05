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

		// glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glGenTextures(1, &rendererID);
		glBindTexture(GL_TEXTURE_2D, rendererID);

		// glTextureStorage2D(rendererID, 1, GL_RGB8, width, height);
		
		// glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum internalFormat = 0, dataFormat = 0;

		switch (channels) {
		case 4:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;
		case 3:
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		CRYSTAL_CORE_ASSERT(internalFormat && dataFormat, "Format not supported!");

		// glTexturecSubImage2D(rendererID, 0, 0, 0, width, height, GL_RGB8, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		// glBindTextureUnit(slot, rendererID);
		glBindTexture(slot, rendererID);
	}

}