#pragma once

#include <functional>

#include "crystal/debug/Instrumentor.h"
#include "crystal/core/Base.h"

using namespace std;

namespace Crystal 
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		Tick, Update, Render,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// BIT defined in Base.h
	// Using bit field to have multiple categories: 000000110 = Input + Keyboard
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override { return category; }

	class Event 
	{	
	public:
		virtual ~Event() = default;

		bool handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategory() const = 0;
		virtual string ToString() const { return GetName(); }

		bool IsCategory(EventCategory category)
		{
			return GetCategory() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& function)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled |= function(static_cast<T&>(event));
				return true;
			}

			return false;
		}
	private:
		Event& event;
	};

	inline ostream& operator<<(ostream& stream, const Event& event)
	{
		return stream << event.ToString();
	}
}
