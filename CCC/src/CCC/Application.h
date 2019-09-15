#pragma once

#include "Core.h"
#include <CCC\Window.h>

namespace CCC
{
	class CCC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in a client
	Application* CreateApplication();

}