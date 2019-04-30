#pragma once

#include "crystalpch.h"

#include "crystal/Core.h"
#include "crystal/events/Event.h"

using namespace std;

namespace Crystal
{
	struct WindowProperties
	{
		string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const string& title = "Crystal Engine", unsigned int width = 1280, unsigned int height = 720)
		{
			this->title = title;
			this->width = width;
			this->height = height;
		}
	};

	class CRYSTAL_API Window
	{
	public:
		using EventCallbackFunction = function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}