#include "CCCpch.h"
#include "RenderCommand.h"
#include "OpenGLRendererAPI.h"

namespace CCC
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
