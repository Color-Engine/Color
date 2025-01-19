#pragma once

#include "Core/Layer.h"
#include "Scene/Scene.h"

namespace Sandbox
{
	class Sandbox2D : public Color::Layer
	{
	public:
		Sandbox2D();

		virtual void OnAttach() override;
		virtual void OnUpdate(Color::Timestep ts) override;
		virtual void OnDetach() override;
	private:
		Color::Ref<Color::Scene> m_Scene;
	};
}
