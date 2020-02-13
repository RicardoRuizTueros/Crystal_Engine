#pragma once

#include "crystal/core/Core.h"
#include "crystal/events/Event.h"

#include "crystal/core/Timestep.h"

using namespace std;

namespace Crystal
{
	class Layer
	{
	public:
		Layer(const string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		
		inline const string& GetName() const { return debugName; }
	protected:
		string debugName;
	};
}



