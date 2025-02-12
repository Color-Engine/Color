#pragma once

#include "Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Color
{
	enum class GraphicsAPI
	{
		None = 0,
		// Specifically, the OpenGL 4.6 version.
		OpenGL
	};
	
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetLineWidth(float width) = 0;

		virtual void DrawLines(const Ref<VertexArray>& vertexArray, size_t vertexCount) = 0;
		virtual void DrawIndices(const Ref<VertexArray>& vertexArray, size_t indexCount = 0) = 0;

		static GraphicsAPI GetAPI() { return s_API; }
		static Scope<RendererAPI> New();
	private:
		inline static GraphicsAPI s_API = GraphicsAPI::OpenGL;
	};
}
