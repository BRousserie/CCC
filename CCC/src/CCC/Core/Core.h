#pragma once

#include <memory>

#ifdef CCC_PLATFORM_WINDOWS
#if CCC_DYNAMIC_LINK
	#ifdef CCC_BUILD_DLL
		#define CCC_API __declspec(dllexport)
	#else
		#define CCC_API __declspec(dllimport)
	#endif
#else
	#define CCC_API
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

namespace CCC
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}