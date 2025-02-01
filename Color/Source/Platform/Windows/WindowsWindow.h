#pragma once

#include "Platform/Desktop/DesktopWindow.h"

namespace Color
{
	class WindowsWindow : public DesktopWindow
	{
	public:
		WindowsWindow(const WindowSpec& spec = {});
	};
}
