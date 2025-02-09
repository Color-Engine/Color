#include "EnginePCH.h"
#include "DesktopInput.h"

#include <GLFW/glfw3.h>

namespace Color
{
	DesktopInput::DesktopInput(const Ref<Window>& window)
		: m_Window(window)
	{
		CL_CORE_ASSERT(window, "Input's target window is null!");
	}

	InputState DesktopInput::GetKeyState(KeyCode keycode) const
	{
		if (m_Window.expired())
		{
			CL_CORE_ERROR("Input's target window has expired (i.e. deleted/released from memory)!");
			return InputState::None;
		}

		GLFWwindow* handle = (GLFWwindow*) m_Window.lock()->GetNativeWindow();
		return (InputState) glfwGetKey(handle, keycode);
	}

	InputState DesktopInput::GetMouseButtonState(MouseCode button) const
	{
		if (m_Window.expired())
		{
			CL_CORE_ERROR("Input's target window has expired (i.e. deleted/released from memory)!");
			return InputState::None;
		}

		GLFWwindow* handle = (GLFWwindow*) m_Window.lock()->GetNativeWindow();
		return (InputState) glfwGetMouseButton(handle, button);
	}

	glm::vec2 DesktopInput::GetMousePosition() const
	{
		if (m_Window.expired())
		{
			CL_CORE_ERROR("Input's target window has expired (i.e. deleted/released from memory)!");
			return {};
		}

		GLFWwindow* handle = (GLFWwindow*) m_Window.lock()->GetNativeWindow();
		double xpos, ypos;

		glfwGetCursorPos(handle, &xpos, &ypos);
		return { (float) xpos, (float) ypos };
	}
}
