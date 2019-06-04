#pragma once

#include "Event.h"

using namespace std;

namespace Crystal
{

	class CRYSTAL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		inline float GetX() const { return x; }
		inline float GetY() const { return y; }

		string ToString() const override
		{
			stringstream stream;
			stream << "MouseMovedEvent: " << x << ", " << y;

			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float x, y;
	};

	class CRYSTAL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
		{
			this->xOffset = xOffset;
			this->yOffset = yOffset;
		}

		inline float GetXOffset() const { return xOffset; }
		inline float GetYOffset() const { return yOffset; }

		string ToString() const override
		{
			stringstream stream;
			stream << "MouseScrolledEvent: " << xOffset << ", " << yOffset;

			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float xOffset, yOffset;
	};

	class CRYSTAL_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		int button;

		MouseButtonEvent(int button)
		{
			this->button = button;
		}
	};

	class CRYSTAL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button)
		{
			this->button = button;
		}

		string ToString() const override
		{
			stringstream stream;
			stream << "MouseButtonPressedEvent: " << button;

			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CRYSTAL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
		{
			this->button = button;
		}

		string ToString() const override
		{
			stringstream stream;
			stream << "MouseButtonReleasedEvent: " << button;

			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}