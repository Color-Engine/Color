#include "EnginePCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Color
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CL_CORE_ASSERT(windowHandle != nullptr, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			CL_CORE_FATAL("The graphics context couldn't be created due to a Glad initialization error! OpenGL functions couldn't be imported.");
		}

		CL_CORE_INFO("OpenGL Info:");
		CL_CORE_INFO("  Vendor     -> {}", (const char*) glGetString(GL_VENDOR));
		CL_CORE_INFO("  Renderer   -> {}", (const char*) glGetString(GL_RENDERER));
		CL_CORE_INFO("  Version    -> {}", (const char*) glGetString(GL_VERSION));
		CL_CORE_INFO("  SL Version -> {}", (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5))
		{
			CL_CORE_FATAL
			(
				"The current renderer (called video card/GPU and etc.) is incompatible with the Color Engine. "
				"Color requires a renderer with at least OpenGL 4.5 functionality, the current renderer only supports up to {}.{}. "
				"Try upgrading the graphics driver in order to get the newest OpenGL driver functionality. "
				"Alternatively, you could try changing the renderer with another compatible one if you have one.",
				GLVersion.major, GLVersion.minor
			);
		}
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
