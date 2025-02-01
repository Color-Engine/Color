#pragma once

#include "Core/Layer.h"

#include <vector>

namespace Color
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		/** Ownership is taken over when pushed, lifetime of the layer will be the same as the layer stack's. */
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		/** Ownership is released when popped, the caller must dispose of the layer. */
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		/** Contrary to PopLayer and PopOverlay, this will dispose/release/free the layers and overlays from memory. */
		void PopAll();

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
		std::vector<Layer*>::const_reverse_iterator crbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator crend() const { return m_Layers.rend(); }
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_iterator cbegin() const { return m_Layers.cbegin(); }
		std::vector<Layer*>::const_iterator cend() const { return m_Layers.cend(); }

		const std::vector<Layer*>& GetLayers() const { return m_Layers; }
	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};
}
