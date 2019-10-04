#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace CCC
{

	class Renderer
	{
	public:
		inline static void Init() { RenderCommand::Init(); }
		static void OnWindowResize(uint32_t width, uint32_t height)
			{ RenderCommand::SetViewport(0, 0, width, height); }
			
		inline static void BeginScene(OrthographicCamera& camera)
			{ s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix(); }
		
		inline static void EndScene() {}

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}
