#pragma once

#include "Platform/Desktop/DesktopWindow.h"

namespace Color
{
	class LinuxWindow : public DesktopWindow
	{
	public:
		LinuxWindow(const WindowSpec& spec = {});
	};
}
