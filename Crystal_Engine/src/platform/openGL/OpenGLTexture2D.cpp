#include "crystalpch.h"

#include "platform/openGL/OpenGLTexture2D.h"

#include <stb_image.h>

namespace Crystal
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: width(width), height(height)
	{
		CRYSTAL_PROFILE_FUNCTION();

		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, width, height);
		
		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const string& path) : path(path)
	{
		CRYSTAL_PROFILE_FUNCTION();

		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		
		{
			CRYSTAL_PROFILE_SCOPE("stbi_load");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}

		CRYSTAL_CORE_ASSERT(data, "Failed to load texture!");

		this->height = height;
		this->width = width;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		CRYSTAL_CORE_ASSERT(internalFormat && dataFormat, "Texture format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
		glTextureStorage2D(rendererID, 1, internalFormat, width, height);

		glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		CRYSTAL_PROFILE_FUNCTION();

		glDeleteTextures(1, &rendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		CRYSTAL_PROFILE_FUNCTION();

		uint32_t bytesPerPixel = dataFormat == GL_RGBA ? 4 : 3;
		CRYSTAL_CORE_ASSERT(size == width * height * bytesPerPixel, "Data size must match the texture size!");
		glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindTextureUnit(slot, rendererID);
	}
}