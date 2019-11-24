#pragma once

#include "crystal/renderer/RendererAPI.h"

using namespace glm;
using namespace std;

namespace Crystal
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Reference<VertexArray>& vertexArray) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}