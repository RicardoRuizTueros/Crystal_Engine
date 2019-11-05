#include "crystalpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "platform/openGL/OpenGLShader.h"

namespace Crystal
{
	Shader* Shader::Create(const string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is not supported!")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Shader* Shader::Create(const string& vertexSource, const string& fragmentSource)
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