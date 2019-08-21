#include "crystalpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/gl.h>

namespace Crystal
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : windowHandle(windowHandle)
	{
		CRYSTAL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CRYSTAL_CORE_ASSERT(status, "Failed to initialize Glad");
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}