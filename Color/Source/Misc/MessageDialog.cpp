#include "EnginePCH.h"
#include "MessageDialog.h"

#include "Platform/Windows/WindowsMessageDialog.h"
#include "Platform/Linux/LinuxMessageDialog.h"

namespace Color
{
	Scope<MessageDialog> MessageDialog::New(std::string_view caption, std::string_view content, DialogControls controls, DialogIcon icon)
	{
		return MakeScope<CL_ConcatWithPlatformName(MessageDialog)>(caption, content, controls, icon);
	}
}
