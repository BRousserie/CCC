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

#ifdef CCC_DEBUG
	#define CCC_ENABLE_ASSERTS
#endif

#ifdef CCC_ENABLE_ASSERTS
	#define CCC_ASSERT(x, ...) { if(!(x)) {CCC_ERROR("Assertion failed : {0}", __VA_ARGS__); __debugbreak(); } }
	#define CCC_CORE_ASSERT(x, ...) { if(!(x)) { CCC_CORE_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CCC_ASSERT(x, ...)
	#define CCC_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define CCC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)