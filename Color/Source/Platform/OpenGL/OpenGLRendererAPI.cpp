#include "EnginePCH.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Color
{
	static void OpenGLMessageCallback
	(
		unsigned src,
		unsigned type,
		unsigned id,
		unsigned severity,
		int len,
		const char* msg,
		const void* user
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         CL_CORE_FATAL(msg); break;
		case GL_DEBUG_SEVERITY_MEDIUM:       CL_CORE_ERROR(msg); break;
		case GL_DEBUG_SEVERITY_LOW:          CL_CORE_WARN(msg);  break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: CL_CORE_TRACE(msg); break;
		}

		CL_CORE_ASSERT(false, "Unknown GLDebugMessageSeverity!");
	}

	void OpenGLRendererAPI::Init()
	{
	#ifdef CL_TEST_BUILD
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OpenGLMessageCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, size_t vertexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertexCount);
	}

	void OpenGLRendererAPI::DrawIndices(const Ref<VertexArray>& vertexArray, size_t indexCount)
	{
		CL_CORE_ASSERT(indexCount || (vertexArray->GetIndexBuffer() && vertexArray->GetIndexBuffer()->GetCount()), "Invalid amount of indices to draw!");
		size_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, (GLsizei) count, GL_UNSIGNED_INT, nullptr);
	}
}
