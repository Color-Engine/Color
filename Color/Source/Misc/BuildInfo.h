#pragma once

#include <string_view>

namespace Color
{
	enum class BuildConfig
	{
		Development,
		Preview,
		Shipping
	};

	enum class Architecture
	{
		x64,
		ARM64
	};

	inline std::string_view ArchitectureToString(Architecture arch)
	{
		switch (arch)
		{
		case Architecture::x64:   return "x64";
		case Architecture::ARM64: return "ARM64";
		default: break;
		}

		return {};
	}

	#ifdef CL_DEVELOPMENT
		inline constexpr BuildConfig c_BuildCfg = BuildConfig::Development;
	#elif defined CL_PREVIEW
		inline constexpr BuildConfig c_BuildCfg = BuildConfig::Preview;
	#elif defined CL_SHIPPING
		inline constexpr BuildConfig c_BuildCfg = BuildConfig::Shipping;
	#else
		#error Unknown build configuration!
	#endif

	#ifdef CL_TEST_BUILD
		inline constexpr bool c_IsTestBuild = true;
	#elif defined CL_DIST_BUILD
		inline constexpr bool c_IsTestBuild = false;
	#else
		#error Unknown build type!
	#endif
	inline constexpr bool c_IsDistBuild = !c_IsTestBuild;

	#ifdef CL_ARCH_X64
		inline constexpr Architecture c_Architecture = Architecture::x64;
	#elif defined CL_ARCH_ARM64
		inline constexpr Architecture c_Architecture = Architecture::ARM64;
	#else
		#error Unknown target architecture!
	#endif
	inline constexpr int c_BitWidth = 64; // Go to IntTypes.h for more details. Currently it's always 64. Also known as word size.
}
