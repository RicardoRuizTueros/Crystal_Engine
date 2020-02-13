#include "crystalpch.h"

#include "crystal/renderer/Shader.h"
#include "crystal/renderer/Renderer.h"

#include "platform/openGL/OpenGLShader.h"

using namespace std;

namespace Crystal
{
	Reference<Shader> Shader::Create(const string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is not supported!")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLShader>(filepath);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Reference<Shader> Shader::Create(const string& name, const string& vertexSource, const string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CRYSTAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL:
			return CreateReference<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}