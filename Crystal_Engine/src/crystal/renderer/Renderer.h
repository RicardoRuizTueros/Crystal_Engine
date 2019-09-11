#pragma once

#include "RenderCommand.h"

using namespace std;

namespace Crystal
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}