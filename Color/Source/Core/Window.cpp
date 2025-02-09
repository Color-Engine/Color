#include "EnginePCH.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Linux/LinuxWindow.h"

namespace Color
{
	Ref<Window> Window::New(const WindowSpec& spec)
	{
		return MakeRef<CL_ConcatWithPlatformName(Window)>(spec);
	}
}
