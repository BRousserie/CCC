#pragma once

#ifdef CCC_PLATFORM_WINDOWS
	#ifdef CCC_BUILD_DLL
		#define CCC_API __declspec(dllexport)
	#else
		#define CCC_API __declspec(dllimport)
	#endif
#else
	#error CCC only supports Windows
#endif