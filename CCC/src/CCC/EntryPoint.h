#pragma once
#include "Application.h"

#ifdef CCC_PLATFORM_WINDOWS

extern CCC::Application* CCC::CreateApplication();

int main(int argc, char** argv)
{
	auto app = CCC::CreateApplication();
	app->Run();
	delete app;
}

#endif