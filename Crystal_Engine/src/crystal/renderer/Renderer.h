#pragma once

#include "crystal/renderer/RenderCommand.h"
#include "crystal/renderer/OrthographicCamera.h"
#include "crystal/renderer/Shader.h"

using namespace std;
using namespace glm;

namespace Crystal
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const mat4& transform = mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void OnWindowResize(uint32_t width, uint32_t height);

	private:
		struct SceneData
		{
			mat4 viewProjectionMatrix;
		};

		static Scope<SceneData> sceneData;
	};
}