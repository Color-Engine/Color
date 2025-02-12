#include "EnginePCH.h"
#include "Buffer.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Color
{
	size_t SizeOfShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
		}

		CL_CORE_ASSERT(false);
		return 0;
	}

	Ref<VertexBuffer> VertexBuffer::New(size_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLVertexBuffer>(size);
		case GraphicsAPI::None:
		default:
			break;
		}

		CL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::New(const float* vertices, size_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLVertexBuffer>(vertices, size);
		case GraphicsAPI::None:
		default:
			break;
		}

		CL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::New(const uint32_t* indices, size_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLIndexBuffer>(indices, count);
		case GraphicsAPI::None:
		default:
			break;
		}

		CL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
