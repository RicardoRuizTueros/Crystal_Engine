#pragma once

#include "crystal/core/Core.h"
#include "crystal/layers/Layer.h"

#include <vector>

using namespace std;

namespace Crystal
{
	class LayerStack : Layer
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		vector<Layer*>::iterator begin() { return layers.begin(); }
		vector<Layer*>::iterator end() { return layers.end(); }

	private:
		vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;
	};
}