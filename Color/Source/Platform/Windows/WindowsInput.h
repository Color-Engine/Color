#pragma once

#include "Platform/Desktop/DesktopInput.h"

namespace Color
{
	class WindowsInput : public DesktopInput
	{
	public:
		WindowsInput(const Ref<Window>& window);
	};
}
