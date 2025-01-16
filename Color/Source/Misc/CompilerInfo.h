#pragma once

namespace Color
{
	enum class Compilers
	{
		Unknown = 0,
		MSVC,
		Clang,
		GCC
	};

	struct CompilerInfo
	{
		const char* Name = nullptr;
		const char* Abbreviation = nullptr;
		Compilers Compiler = Compilers::Unknown;

		// Is this compiler fully supported by the engine?
		bool IsSupported = false;
	};

	#define DECLARE_COMPLIER_INFO_VAR(...) inline constexpr CompilerInfo c_CompilerInfo = { __VA_ARGS__ };
	#ifdef __clang__ // Clang must be checked first, after that the order of MSVC & GCC doesn't matter. But Clang must be first.
		#define CL_COMPLIER_CLANG 1
		DECLARE_COMPLIER_INFO_VAR("Clang++", "Clang", Compilers::Clang, true);
	#elif defined _MSC_VER
		#define CL_COMPILER_MSVC 1
		DECLARE_COMPLIER_INFO_VAR("Microsoft Visual C++ Compiler", "MSVC", Compilers::MSVC, true);
	#elif defined __GNUC__
		#define CL_COMPILER_GCC 1
		DECLARE_COMPLIER_INFO_VAR("GNU C++ Compiler", "GCC", Compilers::GCC, true);
	#else
		#warning Unknown/unsupported compiler
		DECLARE_COMPLIER_INFO_VAR("Unknown C++ Compiler", "Unknown", Compilers::Unknown, false);
		#define CL_COMPILER_UNKNOWN 1
	#endif
	#undef DECLARE_COMPLIER_INFO_VAR

	// For some reason, MSVC never sets the __cplusplus to its correct value unless compiled with a specific flag.
	// We have no way of knowing if that flag is used at compile-time, so we cannot rely on __cplusplus with MSVC.
	// However, MSVC always sets _MSVC_LANG to the correct value, so we use _MSVC_LANG for MSVC and __cplusplus for other vendors.
	#ifdef CL_COMPILER_MSVC
		#define CL_CPP_STANDARD _MSVC_LANG
	#else
		#define CL_CPP_STANDARD __cplusplus
	#endif
}
