#include "EnginePCH.h"
#include "LayerStack.h"

namespace Color
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		PopAll();
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto endIt = m_Layers.begin() + m_LayerInsertIndex;
		auto it = std::find(m_Layers.begin(), endIt, layer);
		if (it != endIt)
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	void LayerStack::PopAll()
	{
		while (m_Layers.size())
		{
			Layer* layer = m_Layers[m_Layers.size() - 1];
			layer->OnDetach();
			delete layer;

			m_Layers.pop_back();
		}
	}
}
