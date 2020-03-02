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
		CRYSTAL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CRYSTAL_CORE_ASSERT(status, "Failed to initialize Glad");

		CRYSTAL_CORE_INFO("OpenGL Info:");
		CRYSTAL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CRYSTAL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CRYSTAL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers()
	{
		CRYSTAL_PROFILE_FUNCTION();

		glfwSwapBuffers(windowHandle);
	}
}