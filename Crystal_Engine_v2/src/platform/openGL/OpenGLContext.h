#pragma once

#include "Crystal/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Crystal
{
	class OpenGLContext : public GraphicsContext
	{

	public:
		OpenGLContext(GLFWwindow* windowsHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	
	private:
		GLFWwindow* windowHandle;
	};
}