#include "Sandbox2D.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/VertexArray.h"

namespace Sandbox
{
	Color::Ref<Color::VertexArray>  g_VertexArray;
	Color::Ref<Color::VertexBuffer> g_VertexBuffer;
	Color::Ref<Color::IndexBuffer>  g_IndexBuffer;

	Sandbox2D::Sandbox2D()
		: Layer("Sandbox2D")
	{
	}

	void Sandbox2D::OnAttach()
	{
		CL_INFO("Sandbox2D::OnAttach");

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] =
		{
			0, 1, 2,
			0, 3, 2
		};

		g_VertexArray = Color::VertexArray::New();
		g_VertexArray->Bind();

		g_VertexBuffer = Color::VertexBuffer::New(vertices, sizeof(vertices));
		g_VertexBuffer->SetLayout({
			{ Color::ShaderDataType::Float3, "a_Position" }
		});
		g_VertexBuffer->Bind();

		g_IndexBuffer = Color::IndexBuffer::New(indices, 6);
		g_IndexBuffer->Bind();

		g_VertexArray->AddVertexBuffer(g_VertexBuffer);
		g_VertexArray->SetIndexBuffer(g_IndexBuffer);

		m_Scene = Color::MakeRef<Color::Scene>();
		m_Scene->Start();
	}

	void Sandbox2D::OnUpdate(Color::Timestep ts)
	{
		m_Scene->Update(ts);

		Color::RenderCommand::Clear();
		Color::RenderCommand::DrawIndices(g_VertexArray);
	}

	void Sandbox2D::OnDetach()
	{
		CL_INFO("Sandbox2D::OnDetach");

		m_Scene->Stop();
		m_Scene.reset();
	}
}
