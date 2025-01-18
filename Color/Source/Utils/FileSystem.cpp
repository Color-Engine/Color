#include "EnginePCH.h"
#include "FileSystem.h"

#include "Platform/Windows/WindowsFileSystem.h"
#include "Platform/Linux/LinuxFileSystem.h"

namespace Color
{
	Scope<NativeFileSystem> FileSystem::s_NativeFS = MakeScope<CL_ConcatWithPlatformName(FileSystem)>();
}
