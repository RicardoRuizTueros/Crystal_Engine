#include <crystalpch.h>
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Crystal
{
	void Crystal::OpenGLRendererAPI::SetClearColor(const vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Crystal::OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Crystal::OpenGLRendererAPI::DrawIndexed(const Reference<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
