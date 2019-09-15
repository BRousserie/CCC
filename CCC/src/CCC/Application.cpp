#include "CCCpch.h"
#include "Application.h"

namespace CCC {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void CCC::Application::Run()
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}

}