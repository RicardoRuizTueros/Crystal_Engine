#pragma once

#include "crystalpch.h"
#include "crystal/Events/Event.h"
#include "crystal/core/Input.h"

using namespace std;

namespace Crystal
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyCode keycode;

		KeyEvent(KeyCode keycode)
		{
			this->keycode = keycode;
		}
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode)
		{
			this->keycode = keycode;
			this->repeatCount = repeatCount;
		}

		int GetRepeatCount() const { return repeatCount; }

		string ToString() const override
		{
			stringstream stream;
			stream << "KeyPressedEvent: " << keycode << " " << repeatCount << " times";

			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode)
		{
			this->keycode = keycode;
		}

		string ToString() const override
		{
			stringstream stream;
			stream << "KeyTypedEvent: " << keycode;

			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	private:
		int repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode)
		{
			this->keycode = keycode;
		}

		string ToString() const override
		{
			stringstream stream;
			stream << "KeyReleasedEvent: " << keycode;

			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}