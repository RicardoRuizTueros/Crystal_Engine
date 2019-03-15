#pragma once

#include "crystalpch.h"
#include "Event.h"

using namespace std;

namespace Crystal
{
	class CRYSTAL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keycode; }


		virtual int GetCategory() const override { return EventCategoryKeyboard | EventCategoryInput; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		int keycode;

		KeyEvent(int keycode)
		{
			this->keycode = keycode;
		}
	};

	class CRYSTAL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode)
		{
			this->keycode = keycode;
			this->repeatCount = repeatCount;
		}

		inline int GetRepeatCount() const { return repeatCount; }

		string ToString() const override
		{
			stringstream stream;
			stream << "KeyPressedEvent: " << keycode << " " << repeatCount << " times" << endl;

			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};

	class CRYSTAL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode)
		{
			this->keycode = keycode;
		}

		string ToString() const override
		{
			stringstream stream;
			stream << "KeyReleasedEvent: " << keycode << endl;

			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}