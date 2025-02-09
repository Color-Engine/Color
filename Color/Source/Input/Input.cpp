#include "EnginePCH.h"
#include "Input.h"

#include "Platform/Windows/WindowsInput.h"
#include "Platform/Linux/LinuxWindow.h"

namespace Color
{
	Scope<NativeInput> Input::s_Instance = nullptr;

	Scope<NativeInput> NativeInput::New(const Ref<Window>& window)
	{
		return MakeScope<CL_ConcatWithPlatformName(Input)>(window);
	}

	void Input::Init(const Ref<Window>& window)
	{
		CL_CORE_ASSERT(!s_Instance);
		s_Instance = NativeInput::New(window);
	}
}
