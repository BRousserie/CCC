#include <CCC.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public CCC::Layer
{
public:
	ExampleLayer()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), Layer("Example"), m_CameraPosition(0.0f)
	{

#pragma region Triangle

		m_VertexArray.reset(CCC::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<CCC::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(CCC::VertexBuffer::Create(vertices, sizeof(vertices)));

		CCC::BufferLayout layout = {
			{ CCC::ShaderDataType::Float3, "a_Position" },
			{ CCC::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<CCC::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(CCC::IndexBuffer::Create(
			indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
	
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
		
			void main()
			{
				color = v_Color;
			}
	
		)";

		m_Shader.reset(new CCC::Shader(vertexSrc, fragmentSrc));

#pragma endregion

#pragma region Square
		m_SquareVA.reset(CCC::VertexArray::Create());
		float sqrVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};
		std::shared_ptr<CCC::VertexBuffer> squareVB;
		squareVB.reset(CCC::VertexBuffer::Create(sqrVertices, sizeof(sqrVertices)));

		squareVB->SetLayout({
			{ CCC::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t sqrIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<CCC::IndexBuffer> squareIB;
		squareIB.reset(CCC::IndexBuffer::Create(sqrIndices, sizeof(sqrIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

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

			uniform vec4 u_Color;
		
			void main()
			{
				color = u_Color;
			}
	
		)";

		m_flatColorShader.reset(new CCC::Shader(flatColorVertexSrc, flatColorFragmentSrc));
#pragma endregion

	}
	void OnUpdate(CCC::Timestep ts) override
	{
		CCC_TRACE("Delta time : {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (CCC::Input::IsKeyPressed(CCC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (CCC::Input::IsKeyPressed(CCC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (CCC::Input::IsKeyPressed(CCC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (CCC::Input::IsKeyPressed(CCC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (CCC::Input::IsKeyPressed(CCC_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed * ts;
		if (CCC::Input::IsKeyPressed(CCC_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed * ts;

		CCC::RenderCommand::SetClearColor({ 0.1, 0.2, 0.3, 1 });
		CCC::RenderCommand::Clear();

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition({ m_CameraPosition });

		CCC::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 != y%2)
					m_flatColorShader->UploadUniformFloat4("u_Color", redColor);
				else
					m_flatColorShader->UploadUniformFloat4("u_Color", blueColor);
				CCC::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
			}
		}
		//CCC::Renderer::Submit(m_Shader, m_VertexArray);
		CCC::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(CCC::Event& event) override
	{
	}

private:
	std::shared_ptr<CCC::Shader> m_Shader;
	std::shared_ptr<CCC::VertexArray> m_VertexArray;

	std::shared_ptr<CCC::Shader> m_flatColorShader;
	std::shared_ptr<CCC::VertexArray> m_SquareVA;

	CCC::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotateSpeed = 90.0f;
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