#pragma once

#include <memory>

#include "crystal/core/PlatformDetection.h"

#ifdef CRYSTAL_DEBUG
	#ifdef CRYSTAL_PLATFORM_WINDOWS
		#define CRYSTAL_DEBUGBREAK __debugbreak()
	#elif defined CRYSTAL_PLATFORM_LINUX
		#include <signal.h>
		#define CRYSTAL_DEBUGBREAK raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
#endif
	#define CRYSTAL_ENABLE_ASSERTS
#endif

#ifdef CRYSTAL_ENABLE_ASSERTS
	#define CRYSTAL_ASSERT(x, ...) { if(!x) { CRYSTAL_ERROR("Assertion Failed: {0}", __VA_ARGS__); CRYSTAL_DEBUGBREAK; }}
	#define CRYSTAL_CORE_ASSERT(x, ...) { if(!x) { CRYSTAL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); CRYSTAL_DEBUGBREAK; }}
#else
	#define CRYSTAL_ASSERT(x, ...)
	#define CRYSTAL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CRYSTAL_BIND_EVENT_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Crystal
{
	template<typename T> using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T> using Reference = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Reference<T> CreateReference(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
