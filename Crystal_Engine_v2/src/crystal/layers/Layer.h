#pragma once

#include "Crystal/Core.h"
#include "Crystal/Events/Event.h"

using namespace std;

namespace Crystal
{
	class CRYSTAL_API Layer
	{
	public:
		Layer(const string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const string& GetName() const { return debugName; }
	protected:
		string debugName;
	};
}



