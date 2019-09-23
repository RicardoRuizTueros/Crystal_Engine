#pragma once

#include "crystal\layers\Layer.h"
#include <crystal\events\MouseEvent.h>
#include <crystal\events\KeyEvent.h>
#include <crystal\events\ApplicationEvent.h>

namespace Crystal
{
	class CRYSTAL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float lastTime;
	};
}