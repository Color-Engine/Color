#include "EnginePCH.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Color
{
	static void CreateAndSetupBufferGL(uint32_t& id, GLenum type, const void* data, size_t size, GLenum usage)
	{
		glCreateBuffers(1, &id);
		glBindBuffer(type, id);
		glBufferData(type, size, data, usage);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
	{
		CreateAndSetupBufferGL(m_RendererID, GL_ARRAY_BUFFER, nullptr, size, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, size_t size)
	{
		CreateAndSetupBufferGL(m_RendererID, GL_ARRAY_BUFFER, vertices, size, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, size_t count)
		: m_Count(count)
	{
		CreateAndSetupBufferGL(m_RendererID, GL_ELEMENT_ARRAY_BUFFER, indices, count * sizeof(uint32_t), GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
