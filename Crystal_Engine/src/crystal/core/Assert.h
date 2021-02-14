#pragma once

#include "Crystal/core/Base.h"
#include "Crystal/core/Log.h"
#include <filesystem>

#ifdef CRYSTAL_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define CRYSTAL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CRYSTAL##type##ERROR(msg, __VA_ARGS__); CRYSTAL_DEBUGBREAK; } }
#define CRYSTAL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CRYSTAL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define CRYSTAL_INTERNAL_ASSERT_NO_MSG(type, check) CRYSTAL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CRYSTAL_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define CRYSTAL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define CRYSTAL_INTERNAL_ASSERT_GET_MACRO(...) CRYSTAL_EXPAND_MACRO( CRYSTAL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CRYSTAL_INTERNAL_ASSERT_WITH_MSG, CRYSTAL_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define CRYSTAL_ASSERT(...) CRYSTAL_EXPAND_MACRO( CRYSTAL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define CRYSTAL_CORE_ASSERT(...) CRYSTAL_EXPAND_MACRO( CRYSTAL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define CRYSTAL_ASSERT(...)
#define CRYSTAL_CORE_ASSERT(...)
#endif
