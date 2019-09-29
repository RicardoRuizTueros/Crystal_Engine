#pragma once

#include "crystal/renderer/Texture2D.h"

namespace Crystal
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		string path;
		uint32_t width, height, rendererID;
	};
}