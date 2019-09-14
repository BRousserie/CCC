#pragma once
#include "Application.h"
#include "Log.h"

#ifdef CCC_PLATFORM_WINDOWS

extern CCC::Application* CCC::CreateApplication();

int main(int argc, char** argv)
{
	CCC::Log::Init();

	auto app = CCC::CreateApplication();
	app->Run();
	delete app;
}

#endif