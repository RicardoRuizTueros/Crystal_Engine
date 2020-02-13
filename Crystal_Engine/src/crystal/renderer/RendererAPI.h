#pragma once

#include <glm/glm.hpp>

#include "crystal/renderer/VertexArray.h"

using namespace glm;
using namespace std;

namespace Crystal
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual void Init() = 0;
		virtual void SetClearColor(const vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return api; }
		static Scope<RendererAPI> Create();

	private:
		static API api;
	};
}