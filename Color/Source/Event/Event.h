#pragma once

#include "Core/Base.h"

#include <string_view>
#include <string>

namespace Color
{
	using EventCategory = int;
	enum : int
	{
		EC_None               = 0,
		EC_Application = CL_BIT(0),
		EC_Input       = CL_BIT(1),
		EC_Keyboard    = CL_BIT(2),
		EC_Mouse       = CL_BIT(3),
		EC_MouseButton = CL_BIT(4)
	};

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
		AppTick, AppUpdate, AppRender,
		KeyPress, KeyType, KeyRelease,
		MouseMove, MouseScroll,
		MouseButtonPress, MouseButtonRelease
	};

	#define EVENT_TYPE_DETAIL(type) \
		static ::Color::EventType GetStaticType() { return ::Color::EventType::##type; } \
		virtual std::string_view GetName() const override { return #type; } \
		virtual ::Color::EventType GetType() const override { return GetStaticType(); }

	#define EVENT_CATEGORY_DETAIL(categoryFlags) \
		virtual ::Color::EventCategory GetCategoryFlags() const override { return categoryFlags; }

	class Event
	{
	public:
		bool Handled = false;
	public:
		virtual ~Event() = default;

		virtual std::string_view GetName() const = 0;
		virtual EventType GetType() const = 0;
		virtual EventCategory GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName().data(); }

		bool HasCategoryFlags(EventCategory categoryFlags) const
		{
			return GetCategoryFlags() & categoryFlags;
		}
	};

	class ApplicationEvent : public Event
	{
	public:
		EVENT_CATEGORY_DETAIL(EC_Application);
	};

	class InputEvent : public Event
	{
	public:
		EVENT_CATEGORY_DETAIL(EC_Input);
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T, typename F>
		bool Dispatch(const F& target)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.Handled |= target((T&) m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}

template <typename OStream>
inline OStream& operator<<(OStream& stream, const Color::Event& e)
{
	return stream << e.ToString();
}
