#include "crystalpch.h"

#include "crystal/renderer/Renderer.h"
#include "crystal/renderer/Renderer2D.h"

using namespace glm;
using namespace std;

namespace Crystal
{
	Scope<Renderer::SceneData> Renderer::sceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		CRYSTAL_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sceneData->viewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_viewProjection", sceneData->viewProjectionMatrix);
		shader->SetMat4("u_transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}