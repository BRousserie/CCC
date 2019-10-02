#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Platform/OpenGL/OpenGLShader.h"

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

		inline static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f))
		{
			shader->Bind();
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
			
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
