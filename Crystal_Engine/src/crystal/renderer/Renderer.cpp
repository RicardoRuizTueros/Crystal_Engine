#include "crystalpch.h"
#include "Renderer.h"

namespace Crystal
{

	void Renderer::BeginScene()
	{
		
	}
	void Renderer::EndScene()
	{

	}
	
	void Renderer::Submit(const shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}