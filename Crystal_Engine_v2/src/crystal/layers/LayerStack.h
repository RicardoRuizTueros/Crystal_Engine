#pragma once

#include "Crystal/Core.h"
#include "Layer.h"

#include <vector>

using namespace std;

namespace Crystal
{
	class CRYSTAL_API LayerStack : Layer
	{
	public:
		LayerStack();
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