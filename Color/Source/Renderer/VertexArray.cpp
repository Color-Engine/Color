#include "EnginePCH.h"
#include "VertexArray.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Color
{
	Ref<VertexArray> VertexArray::New()
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLVertexArray>();
		case GraphicsAPI::None:
		default:
			break;
		}

		CL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
