#pragma once

#include "../Core.h"

#include <string>
#include <functional>

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
	enum class EventCategory
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
								virtual const char* GetName() override { return ##type; }

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

}