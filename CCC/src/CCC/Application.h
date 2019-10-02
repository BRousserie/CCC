#pragma once

#include "Core.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

#include "CCC/ImGui/ImGuiLayer.h"

namespace CCC
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in a client
	Application* CreateApplication();

}
