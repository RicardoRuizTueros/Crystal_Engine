#include "crystalpch.h"
#include "LayerStack.h"

using namespace std;

namespace Crystal
{
	LayerStack::LayerStack()
	{

	}

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
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layers.emplace_back(layer);
		layer->OnAttach();
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
