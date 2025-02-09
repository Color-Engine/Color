#pragma once

#include "Input/Input.h"

namespace Color
{
	class DesktopInput : public NativeInput
	{
	public:
		DesktopInput(const Ref<Window>& window);

		virtual InputState GetKeyState(KeyCode keycode) const override;
		virtual InputState GetMouseButtonState(MouseCode button) const override;
		virtual glm::vec2 GetMousePosition() const override;
	private:
		std::weak_ptr<Window> m_Window;
	};
}
