#include "crystalpch.h"

#include "platform/openGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Crystal
{
	void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, 
		unsigned severity, int length, const char* message, const void* userParameters)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			CRYSTAL_CORE_CRITICAL(message);
			return;
		case GL_DEBUG_SEVERITY_MEDIUM:
			CRYSTAL_CORE_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_LOW:
			CRYSTAL_CORE_WARNING(message);
			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			CRYSTAL_CORE_TRACE(message);
			return;
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown severity level");
	}

	void OpenGLRendererAPI::Init()
	{
		CRYSTAL_PROFILE_FUNCTION();

#ifdef CRYSTAL_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);	
	}
}
