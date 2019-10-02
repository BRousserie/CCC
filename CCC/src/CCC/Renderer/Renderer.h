#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace CCC
{

	class Renderer
	{
	public:
		inline static void BeginScene(OrthographicCamera& camera)
		{
			m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		}
		
		inline static void EndScene() {}

		inline static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
		{
			shader->Bind();
			shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
			vertexArray->Bind();
			RenderCommand::DrawIndexed(vertexArray);
		}

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
