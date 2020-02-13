#include <crystalpch.h>

#include "crystal/renderer/RenderCommand.h"

namespace Crystal
{
	Scope<RendererAPI> RenderCommand::rendererAPI = RendererAPI::Create();
}