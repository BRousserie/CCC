#pragma once

#include "RenderCommand.h"

namespace CCC
{

	class Renderer
	{
	public:
		inline static void BeginScene() {}
		inline static void EndScene() {}

		inline static void Submit(const std::shared_ptr<VertexArray>& vertexArray)
		{
			vertexArray->Bind();
			RenderCommand::DrawIndexed(vertexArray);
		}

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
