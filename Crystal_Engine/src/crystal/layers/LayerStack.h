#pragma once

#include "crystal/core/Base.h"
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

		vector<Layer*>::reverse_iterator reverse_begin() { return layers.rbegin(); }
		vector<Layer*>::reverse_iterator reverse_end() { return layers.rend(); }

		vector<Layer*>::const_iterator begin() const { return layers.begin(); }
		vector<Layer*>::const_iterator end() const { return layers.end(); }

		vector<Layer*>::const_reverse_iterator reverse_begin() const { return layers.rbegin(); }
		vector<Layer*>::const_reverse_iterator reverse_end() const { return layers.rend(); }



	private:
		vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;
	};
}