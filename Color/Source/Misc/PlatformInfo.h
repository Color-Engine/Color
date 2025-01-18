#pragma once

#include "Misc/MiscDefines.h"

namespace Color
{
	enum class Platforms
	{
		Windows,
		Linux
	};

	#ifdef CL_PLATFORM_WINDOWS
		#define CL_PLATFORM_NAME Windows
		inline constexpr Platforms c_Platform = Platforms::Windows;
	#elif defined CL_PLATFORM_LINUX
		#define CL_PLATFORM_NAME Linux
		inline constexpr Platforms c_Platform = Platforms::Linux;
	#else
		#error Unknown platform, Color only supports Windows and Linux as of now!
	#endif

	#define CL_PLATFORM_NAME_STRING CL_STRINGIFY(CL_PLATFORM_NAME)
	#define CL_ConcatWithPlatformName(x) CL_CONCAT(CL_PLATFORM_NAME, x)

	#ifdef CL_STABLE_PLATFORM
		inline constexpr bool c_IsStablePlatform = true;
	#elif defined CL_EXPERIMENTAL_PLATFORM
		inline constexpr bool c_IsStablePlatform = false;
	#else
		#error Unknown platform stability!
	#endif
	inline constexpr bool c_IsExperimentalPlatform = !c_IsStablePlatform;
}
