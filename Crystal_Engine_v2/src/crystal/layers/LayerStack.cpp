#include "crystalpch.h"
#include "LayerStack.h"

namespace Crystal
{
	LayerStack::LayerStack()
	{
		layerInsert = layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iterator = std::find(layers.begin(), layers.end(), layer);
		
		if (iterator != layers.end())
		{
			layers.erase(iterator);
			layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto iterator = std::find(layers.begin(), layers.end(), layer);

		if (iterator != layers.end())
		{
			layers.erase(iterator);
		}
	}
}
