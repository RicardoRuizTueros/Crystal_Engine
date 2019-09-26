#pragma once

#include "RendererAPI.h"

using namespace glm;
using namespace std;

namespace Crystal
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const vec4& color)
		{
			rendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			rendererAPI->Clear();
		}

		inline static void DrawIndexed(const Reference<VertexArray>& vertexArray)
		{
			rendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* rendererAPI;
	};
}