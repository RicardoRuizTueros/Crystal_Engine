#pragma once

#include "crystal\layers\Layer.h"
#include <crystal\events\MouseEvent.h>
#include <crystal\events\KeyEvent.h>
#include <crystal\events\ApplicationEvent.h>

namespace Crystal
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { blockEvents = block; }
	private:
		bool blockEvents = true;
		float lastTime;
	};
}