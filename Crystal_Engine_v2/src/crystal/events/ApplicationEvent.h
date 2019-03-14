#pragma once

#include "Event.h"
#include <sstream>

namespace Crystal
{
	class CRYSTAL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
		{
			this->width = width;
			this->height = height;
		}

		inline unsigned int GetWidth() { return width; }
		inline unsigned int GetHeight() { return height; }

		string ToString() const override
		{
			stringstream stream;
			stream << "WindowResizeEvent: " << width << ", " << height << endl;

			return stream.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int width, height;
	};

	class CRYSTAL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CRYSTAL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(Tick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CRYSTAL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(Update)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CRYSTAL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(Render)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}