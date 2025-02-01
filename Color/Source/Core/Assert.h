#pragma once

#include "Core/Log.h"

#ifdef CL_PLATFORM_WINDOWS
	#define CL_DEBUGBREAK_BASE() __debugbreak()
#else
	#include <signal.h>
	#define CL_DEBUGBREAK_BASE() raise(SIGTRAP)
#endif

#ifdef CL_TEST_BUILD
	#define CL_DEBUGBREAK() CL_DEBUGBREAK_BASE()
	#define CL_ASSERT_BASE(logger, expression, ...) if (!(expression)) { CL_LOGGER_ERROR(logger, "Assertion failed in file '" __FILE__ "' at line " CL_STRINGIFY(__LINE__) "! Expression '" #expression "' evaluted to false. " __VA_ARGS__); CL_DEBUGBREAK(); }
#else
	#define CL_DEBUGBREAK()
	#define CL_ASSERT_BASE(logger, expression, ...)
#endif

#define CL_CORE_ASSERT(expression, ...) CL_ASSERT_BASE(::Color::Log::g_CoreLogger, expression, __VA_ARGS__)
#define CL_ASSERT(expression, ...)      CL_ASSERT_BASE(::Color::Log::g_ClientLogger, expression, __VA_ARGS__)
