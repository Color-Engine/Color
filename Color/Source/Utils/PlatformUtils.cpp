#include "EnginePCH.h"
#include "PlatformUtils.h"

#include "Platform/Windows/WindowsPlatformUtils.h"

namespace Color
{
	Scope<NativePlatformUtils> PlatformUtils::s_NativeUtils = MakeScope<CL_ConcatWithPlatformName(PlatformUtils)>();
}
