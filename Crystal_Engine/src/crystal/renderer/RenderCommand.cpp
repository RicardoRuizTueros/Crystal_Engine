#include <crystalpch.h>
#include "RenderCommand.h"

#include "platform/openGL/OpenGLRendererAPI.h"

namespace Crystal
{
	Scope<RendererAPI> RenderCommand::rendererAPI = CreateScope<OpenGLRendererAPI>();
}