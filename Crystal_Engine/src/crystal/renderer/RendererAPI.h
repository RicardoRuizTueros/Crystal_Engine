#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

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

		virtual void SetClearColor(const vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return api; }

	private:
		static API api;
	};
}