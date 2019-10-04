#include <CCC.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CCC/OrthographicCameraController.h"

class ExampleLayer : public CCC::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{

#pragma region Triangle

		m_VertexArray.reset(CCC::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		CCC::Ref<CCC::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(CCC::VertexBuffer::Create(vertices, sizeof(vertices)));

		CCC::BufferLayout layout = {
			{ CCC::ShaderDataType::Float3, "a_Position" },
			{ CCC::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		CCC::Ref<CCC::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(CCC::IndexBuffer::Create(
			indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);

		m_Shader.reset(new CCC::OpenGLShader("assets/shaders/customVertexColors.glsl"));

#pragma endregion

#pragma region Square
		m_SquareVA.reset(CCC::VertexArray::Create());
		float sqrVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		CCC::Ref<CCC::VertexBuffer> squareVB;
		squareVB.reset(CCC::VertexBuffer::Create(sqrVertices, sizeof(sqrVertices)));

		squareVB->SetLayout({
			{ CCC::ShaderDataType::Float3, "a_Position" },
			{ CCC::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t sqrIndices[6] = { 0, 1, 2, 2, 3, 0 };
		CCC::Ref<CCC::IndexBuffer> squareIB;
		squareIB.reset(CCC::IndexBuffer::Create(sqrIndices, sizeof(sqrIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

#pragma region flatColorShader

		std::string flatColorVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
	
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
		
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
	
		)";

		m_flatColorShader = CCC::Shader::Create("flatColor", flatColorVertexSrc, flatColorFragmentSrc);

#pragma endregion

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = CCC::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = CCC::Texture2D::Create("assets/textures/ChernoLogo.png");
		
		std::dynamic_pointer_cast<CCC::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<CCC::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
		
#pragma endregion
		
	}
	void OnUpdate(CCC::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		CCC::RenderCommand::SetClearColor({ 0.1, 0.2, 0.3, 1 });
		CCC::RenderCommand::Clear();
		
		CCC::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<CCC::OpenGLShader>(m_flatColorShader)->Bind();
		std::dynamic_pointer_cast<CCC::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				CCC::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		CCC::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_ChernoLogoTexture->Bind();
		CCC::Renderer::Submit(textureShader, m_SquareVA, 	glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//CCC::Renderer::Submit(m_Shader, m_VertexArray);
		CCC::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(CCC::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	CCC::ShaderLibrary m_ShaderLibrary;
	
	CCC::Ref<CCC::Shader> m_Shader;
	CCC::Ref<CCC::VertexArray> m_VertexArray;

	CCC::Ref<CCC::Shader> m_flatColorShader;
	CCC::Ref<CCC::VertexArray> m_SquareVA;

	CCC::Ref<CCC::Texture2D> m_Texture, m_ChernoLogoTexture;

	CCC::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Garage : public CCC::Application
{
public:
	Garage()
	{
		PushLayer(new ExampleLayer());
	}

	~Garage() {}

};

CCC::Application* CCC::CreateApplication()
{
	return new Garage();
}