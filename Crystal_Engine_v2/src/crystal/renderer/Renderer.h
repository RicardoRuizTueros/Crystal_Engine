#pragma once

namespace Crystal
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetRendererAPI() { return rendererAPI; }
	private:
		static RendererAPI rendererAPI;
	};
}