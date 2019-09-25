#include <CCC.h>

#include "imgui/imgui.h"

class ExampleLayer : public CCC::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
		if (CCC::Input::IsKeyPressed(CCC_KEY_TAB))
			CCC_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(CCC::Event& event) override
	{
		if (event.GetEventType() == CCC::EventType::KeyPressed)
		{
			CCC::KeyPressedEvent& e = (CCC::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CCC_KEY_TAB)
				CCC_TRACE("Tab key is pressed (event)!");
			CCC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Garage : public CCC::Application
{
public:
	Garage() {}

	~Garage() {}

};

CCC::Application* CCC::CreateApplication()
{
	return new Garage();
}