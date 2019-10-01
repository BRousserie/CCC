#pragma once
#include "CCC/Renderer/RendererAPI.h"

namespace CCC
{
	
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color);
		virtual void Clear();

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
		
	};
	
}

