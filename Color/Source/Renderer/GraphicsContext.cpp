#include "EnginePCH.h"
#include "GraphicsContext.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Color
{
	Scope<GraphicsContext> GraphicsContext::New(void* windowHandle)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLContext>((GLFWwindow*) windowHandle);
		case GraphicsAPI::None:
		default:
			break;
		}

		CL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
