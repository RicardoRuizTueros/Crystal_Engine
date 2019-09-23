#include "crystalpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "platform/openGL/OpenGLShader.h"



namespace Crystal
{
	Shader* Shader::Create(string& vertexSource, string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}