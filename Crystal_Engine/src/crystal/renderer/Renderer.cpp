#include "crystalpch.h"
#include "Renderer.h"

using namespace glm;

namespace Crystal
{
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const shared_ptr<Shader>& shader, const shared_ptr<VertexArray>& vertexArray, const mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_viewProjection", sceneData->viewProjectionMatrix);
		shader->UploadUniformMat4("u_transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}