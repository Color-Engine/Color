#pragma once

#include "Event/Event.h"
#include "Input/MouseCode.h"

#include <sstream>

namespace Color
{
	class MouseEvent : public InputEvent
	{
	public:
		EVENT_CATEGORY_DETAIL(EC_Input | EC_Mouse);
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(float posX, float posY)
			: m_PosX(posX), m_PosY(posY) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_PosX << ", " << m_PosY;
			return ss.str();
		}

		float GetPosX() const { return m_PosX; }
		float GetPosY() const { return m_PosY; }

		EVENT_TYPE_DETAIL(MouseMove);
	private:
		float m_PosX = 0.0f, m_PosY = 0.0f;
	};

	class MouseScrollEvent : public MouseEvent
	{
	public:
		MouseScrollEvent(float offsetX, float offsetY)
			: m_OffsetX(offsetX), m_OffsetY(offsetY) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}

		float GetOffsetX() const { return m_OffsetX; }
		float GetOffsetY() const { return m_OffsetY; }

		EVENT_TYPE_DETAIL(MouseScroll);
	private:
		float m_OffsetX = 0.0f, m_OffsetY = 0.0f;
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseCode GetButton() const { return m_Button; }
		EVENT_CATEGORY_DETAIL(EC_Input | EC_Mouse | EC_MouseButton);
	protected:
		MouseButtonEvent(MouseCode button)
			: m_Button(button) {}
	private:
		MouseCode m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << GetButton();
			return ss.str();
		}

		EVENT_TYPE_DETAIL(MouseButtonPress);
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << GetButton();
			return ss.str();
		}

		EVENT_TYPE_DETAIL(MouseButtonRelease);
	};
}
