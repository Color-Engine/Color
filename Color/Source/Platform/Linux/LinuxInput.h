#pragma once

#include "Platform/Desktop/DesktopInput.h"

namespace Color
{
	class LinuxInput : public DesktopInput
	{
	public:
		LinuxInput(const Ref<Window>& window);
	};
}
