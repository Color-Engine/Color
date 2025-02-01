#include "EnginePCH.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Color
{
	Scope<RendererAPI> RendererAPI::New()
	{
		switch (s_API)
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLRendererAPI>();
		case GraphicsAPI::None:
		default:
			break;
		}

		CL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
