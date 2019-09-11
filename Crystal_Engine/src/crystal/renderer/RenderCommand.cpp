#include <crystalpch.h>
#include "RenderCommand.h"

#include "platform/openGL/OpenGLRendererAPI.h"

namespace Crystal
{
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}