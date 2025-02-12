#pragma once

#include "Renderer/RendererAPI.h"

namespace Color
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetLineWidth(float width) override;

		virtual void DrawLines(const Ref<VertexArray>& vertexArray, size_t vertexCount) override;
		virtual void DrawIndices(const Ref<VertexArray>& vertexArray, size_t indexCount = 0) override;
	};
}
