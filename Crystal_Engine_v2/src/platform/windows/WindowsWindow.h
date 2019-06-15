#pragma once

#include "crystal/Window.h"

#include "GLFW/glfw3.h"

namespace Crystal {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }

		inline void SetEventCallback(const EventCallbackFunction& callback) override { data.callback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		struct WindowData
		{
			string title;
			unsigned int width, height;
			bool vSync;
			EventCallbackFunction callback;
		};

		GLFWwindow* window;
		WindowData data;

		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();
	};
}