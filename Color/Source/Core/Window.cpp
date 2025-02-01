#include "EnginePCH.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Color
{
	Scope<Window> Window::New(const WindowSpec& spec)
	{
		return MakeScope<CL_ConcatWithPlatformName(Window)>(spec);
	}
}
