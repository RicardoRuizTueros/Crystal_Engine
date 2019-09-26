#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

using namespace std;
using namespace glm;

namespace Crystal
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const mat4& transform = mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};
}