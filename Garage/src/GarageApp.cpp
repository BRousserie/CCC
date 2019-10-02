#include <CCC.h>

#include "imgui/imgui.h"

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
		triangleIndexBuffer.reset(CCC::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);
		
		std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};
		std::shared_ptr<CCC::VertexBuffer> squareVB;
		squareVB.reset(CCC::VertexBuffer::Create(sqrVertices, sizeof(sqrVertices)));
		
		squareVB->SetLayout({
			{ CCC::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t sqrIndices[6] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<CCC::IndexBuffer> squareIB;
		squareIB.reset(CCC::IndexBuffer::Create(sqrIndices, sizeof(sqrIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
		
		std::string coloredOnPositionVertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
		
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
	
		)";

		std::string coloredOnPositionFragmentSrc = R"(
			#version 330 core

			layout (location = 0) out vec4 color;

			in vec3 v_Position;
		
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
	
		)";

		m_coloredOnPositionShader.reset(new CCC::Shader(coloredOnPositionVertexSrc, coloredOnPositionFragmentSrc));
#pragma endregion
		
	}
	void OnUpdate() override
	{
		if(CCC::Input::IsKeyPressed(CCC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (CCC::Input::IsKeyPressed(CCC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;
		
		if (CCC::Input::IsKeyPressed(CCC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (CCC::Input::IsKeyPressed(CCC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		
		if (CCC::Input::IsKeyPressed(CCC_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed;
		if (CCC::Input::IsKeyPressed(CCC_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed;
		
		CCC::RenderCommand::SetClearColor({ 0.1, 0.2, 0.3, 1 });
		CCC::RenderCommand::Clear();

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition({ m_CameraPosition });

		CCC::Renderer::BeginScene(m_Camera);
		CCC::Renderer::Submit(m_coloredOnPositionShader, m_SquareVA);
		CCC::Renderer::Submit(m_Shader, m_VertexArray);
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
	
	std::shared_ptr<CCC::Shader> m_coloredOnPositionShader;
	std::shared_ptr<CCC::VertexArray> m_SquareVA;
	
	CCC::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotateSpeed = 2.0f;
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