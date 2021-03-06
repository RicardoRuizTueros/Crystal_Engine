#pragma once

#include "crystal/core/Window.h"
#include "crystal/renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Crystal {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return data.width; }
		unsigned int GetHeight() const override { return data.height; }

		void SetEventCallback(const EventCallbackFunction& callback) override { data.callback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return window; }
	
	private:
		GLFWwindow* window;
		Scope<GraphicsContext> context;

		struct WindowData
		{
			string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFunction callback;
		};

		WindowData data;

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();
	};
}