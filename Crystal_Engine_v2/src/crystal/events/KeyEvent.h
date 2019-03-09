#pragma once

#include "Event.h"

using namespace std;

namespace Crystal
{
	class CRYSTAL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
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
		inline int GetRepeatCount() const { return repeatCount; }

		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent (keycode)
		{
			this->keycode = keycode;
			this->repeatCount = repeatCount;
		}

		string ToString() override
		{
			stringstream stream;
			stream << "KeyPressedEvent: " << keycode << " " << repeatCount << " times" << endl;
			
			return stream.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed)
	private:
		int repeatCount;
	};
}