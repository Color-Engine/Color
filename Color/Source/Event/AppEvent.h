#pragma once

#include "Event/Event.h"
#include "Misc/Timestep.h"

#include <sstream>

namespace Color
{
	class WindowCloseEvent : public ApplicationEvent
	{
	public:
		EVENT_TYPE_DETAIL(WindowClose);
	};

	class WindowResizeEvent : public ApplicationEvent
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		EVENT_TYPE_DETAIL(WindowResize);
	private:
		int m_Width = 0, m_Height = 0;
	};

	class WindowFocusEvent : public ApplicationEvent
	{
	public:
		EVENT_TYPE_DETAIL(WindowFocus);
	};

	class WindowLoseFocusEvent : public ApplicationEvent
	{
	public:
		EVENT_TYPE_DETAIL(WindowLoseFocus);
	};

	class WindowMoveEvent : public ApplicationEvent
	{
	public:
		WindowMoveEvent(int posX, int posY)
			: m_PosX(posX), m_PosY(posY) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMoveEvent: " << m_PosX << ", " << m_PosY;
			return ss.str();
		}

		int GetPosX() const { return m_PosX; }
		int GetPosY() const { return m_PosY; }

		EVENT_TYPE_DETAIL(WindowMove);
	private:
		int m_PosX = 0, m_PosY = 0;
	};

	class AppTickEvent : public ApplicationEvent
	{
	public:
		EVENT_TYPE_DETAIL(AppTick);
	};

	class AppUpdateEvent : public ApplicationEvent
	{
	public:
		EVENT_TYPE_DETAIL(AppUpdate);
	};

	class AppRenderEvent : public ApplicationEvent
	{
	public:
		EVENT_TYPE_DETAIL(AppRender);
	};
}
