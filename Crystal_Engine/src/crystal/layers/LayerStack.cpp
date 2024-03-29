#include "crystalpch.h"
#include "crystal/layers/LayerStack.h"

using namespace std;

namespace Crystal
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iterator = find(layers.begin(), layers.begin() + layerInsertIndex, layer);
		
		if (iterator != layers.begin() + layerInsertIndex)
		{
			layer->OnDetach();
			layers.erase(iterator);
			layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto iterator = find(layers.begin() + layerInsertIndex, layers.end(), layer);

		if (iterator != layers.end())
		{
			layer->OnDetach();
			layers.erase(iterator);
		}
	}
}
