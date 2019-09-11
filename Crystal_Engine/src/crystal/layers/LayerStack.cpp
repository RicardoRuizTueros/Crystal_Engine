#include "crystalpch.h"
#include "LayerStack.h"

namespace Crystal
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iterator = std::find(layers.begin() + layerInsertIndex, layers.end(), layer);
		
		if (iterator != layers.end())
		{
			layer->OnDetach();
			layers.erase(iterator);
			layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto iterator = std::find(layers.begin() + layerInsertIndex, layers.end(), layer);

		if (iterator != layers.end())
		{
			layer->OnDetach();
			layers.erase(iterator);
		}
	}
}
