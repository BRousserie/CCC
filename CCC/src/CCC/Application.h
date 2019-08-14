#pragma once

#include "Core.h"

namespace CCC
{
	class CCC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in a client
	Application* CreateApplication();

}