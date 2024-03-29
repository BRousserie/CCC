#include "CCCpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace CCC
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
