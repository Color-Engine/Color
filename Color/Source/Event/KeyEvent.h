#pragma once

#include "Event/Event.h"
#include "Input/KeyCodes.h"

#include <sstream>

namespace Color
{
	class KeyEvent : public InputEvent
	{
	public:
		KeyCode GetKeyCode() const { return m_Keycode; }
		EVENT_CATEGORY_DETAIL(EC_Input | EC_Keyboard);
	protected:
		KeyEvent(KeyCode keycode)
			: m_Keycode(keycode) {}
	private:
		KeyCode m_Keycode;
	};
	
	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(KeyCode keycode, bool repeat)
			: KeyEvent(keycode), m_Repeat(repeat) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << GetKeyCode() << ", " << m_Repeat;
			return ss.str();
		}

		bool IsRepeat() const { return m_Repeat; }

		EVENT_TYPE_DETAIL(KeyPress);
	private:
		bool m_Repeat = false;
	};

	class KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		EVENT_TYPE_DETAIL(KeyType);
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(KeyCode keycode)
			: KeyEvent(keycode) {
		}

		EVENT_TYPE_DETAIL(KeyRelease);
	};
}
