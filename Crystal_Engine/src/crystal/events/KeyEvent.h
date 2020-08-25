#pragma once

#include "crystalpch.h"
#include "crystal/Events/Event.h"
#include "crystal/core/KeyCodes.h"

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

		KeyEvent(const KeyCode keycode)
		{
			this->keycode = keycode;
		}
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount) : KeyEvent(keycode)
		{
			this->keycode = keycode;
			this->repeatCount = repeatCount;
		}

		uint16_t GetRepeatCount() const { return repeatCount; }

		string ToString() const override
		{
			stringstream stream;
			stream << "KeyPressedEvent: " << keycode << " " << repeatCount << " times";

			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint16_t repeatCount;
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode)
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
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode)
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
