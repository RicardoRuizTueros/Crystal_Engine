#pragma once

#include <sstream>

#include "crystal/core/Base.h"
#include "crystal/events/Event.h"

using namespace std;

namespace Crystal
{
	struct WindowProperties
	{
		string title;
		uint32_t width, height;

		WindowProperties(const string& title = "Crystal Engine", uint32_t width = 1600, uint32_t height = 900)
		{
			this->title = title;
			this->width = width;
			this->height = height;
		}
	};

	class Window
	{
	public:
		using EventCallbackFunction = function<void(Crystal::Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
	};
}
