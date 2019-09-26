#pragma once

#include <memory>

#ifdef CRYSTAL_PLATFORM_WINDOWS
#if CRYSTAL_DYNAMIC_LINK
	#ifdef CRYSTAL_BUILD_DLL
		#define CRYSTAL_API __declspec(dllexport)
	#else
		#define CRYSTAL_API __declspec(dllimport)
	#endif
#else
	#define CRYSTAL_API
#endif
#else
	#error Crystal only supports Window!
#endif

#ifdef CRYSTAL_DEBUG
	#define CRYSTAL_ENABLE_ASSERTS
#endif

#ifdef CRYSTAL_ENABLE_ASSERTS
	#define CRYSTAL_ASSERT(x, ...) { if(!x) { CRYSTAL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CRYSTAL_CORE_ASSERT(x, ...) { if(!x) { CRYSTAL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CRYSTAL_ASSERT(x, ...)
	#define CRYSTAL_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define CRYSTAL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Crystal
{
	template<typename T> using Scope = std::unique_ptr<T>;
	template<typename T> using Reference = std::shared_ptr<T>;
}

