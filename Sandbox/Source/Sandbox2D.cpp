#include "Sandbox2D.h"

namespace Sandbox
{
	Sandbox2D::Sandbox2D()
		: Layer("Sandbox2D")
	{
	}

	void Sandbox2D::OnAttach()
	{
		CL_INFO("Sandbox2D::OnAttach");

		m_Scene = Color::MakeRef<Color::Scene>();
		m_Scene->Start();
	}

	void Sandbox2D::OnUpdate(Color::Timestep ts)
	{
		m_Scene->Update(ts);
	}

	void Sandbox2D::OnDetach()
	{
		CL_INFO("Sandbox2D::OnDetach");

		m_Scene->Stop();
		m_Scene.reset();
	}
}
