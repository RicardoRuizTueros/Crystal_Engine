#pragma once

#include "crystal/Core.h"

#include <string>
#include <functional>
#include <sstream>

using namespace std;

namespace Crystal 
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		Tick, Update, Render,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// BIT defined in Core.h
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

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() override { return GetStaticType(); }\
									virtual const char* GetName() override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() override { return category; }

	class CRYSTAL_API Event 
	{
		friend class EventDispatcher;
	
	public:
		virtual EventType GetEventType();
		virtual const char* GetName();
		virtual int GetCategory();
		virtual string ToString() { return GetName(); }

		inline bool IsCategory(EventCategory category)
		{
			return GetCategory() & category;
		}
		
	protected:
		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T> using EventFunction = function<bool(T&)>;
	public:
		EventDispatcher(Event* event)
		{
			this->event = event;
		}

		template<typename T> bool Dispatch(EventFunction<T> function)
		{
			if (event->GetEventType() == T::GetStaticType())
			{
				event->handled = function(*(T*)&event);
				return true;
			}

			return false;
		}
	private:
		Event* event;
	};

	inline ostream& operator<<(ostream& stream, Event& event)
	{
		return stream << event.ToString();
	}
}