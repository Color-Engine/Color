#pragma once

#include "Renderer/RendererAPI.h"

namespace Color
{
	// Wrapper around the global RendererAPI object.
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_API->Init();
		}

		static void Clear()
		{
			s_API->Clear();
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_API->SetClearColor(color);
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_API->SetViewport(x, y, width, height);
		}

		static void SetLineWidth(float width)
		{
			s_API->SetLineWidth(width);
		}

		static void DrawLines(const Ref<VertexArray>& vertexArray, size_t vertexCount)
		{
			s_API->DrawLines(vertexArray, vertexCount);
		}

		static void DrawIndices(const Ref<VertexArray>& vertexArray, size_t indexCount = 0)
		{
			s_API->DrawIndices(vertexArray, indexCount);
		}
	private:
		static Scope<RendererAPI> s_API;
	};
}
