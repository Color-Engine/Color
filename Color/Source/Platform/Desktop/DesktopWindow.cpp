#include "EnginePCH.h"
#include "DesktopWindow.h"

#include "Event/AppEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Renderer/GraphicsContext.h"
#include "Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

namespace Color
{
	static uint32_t s_WindowCount = 0;

	static void GLFWErrorCallback
	(
		int code,
		const char* desc
	)
	{
		CL_CORE_ERROR("GLFW Error ({0:x}): {1}", code, desc);
	}

	DesktopWindow::DesktopWindow(const WindowSpec& spec)
		: m_Data
		  {
		      spec.Title,
		      spec.Width,
			  spec.Height,
			  spec.Fullscreen,
			  spec.Resizable,
			  spec.VSync,
			  nullptr,

			  SigClose,
			  SigResize,
			  SigFocus,
			  SigLoseFocus,
			  SigMove,
			  SigKeyPress,
			  SigKeyType,
			  SigKeyRelease,
			  SigMouseMove,
			  SigMouseScroll,
			  SigMouseButtonPress,
			  SigMouseButtonRelease
		  }
	{
	}

	DesktopWindow::~DesktopWindow()
	{
		Destroy();
	}

	bool DesktopWindow::Create()
	{
		CL_CORE_INFO("Creating window '{}' ({}x{}) [{}]", m_Data.Title, m_Data.Width, m_Data.Height, m_Data.Fullscreen ? "fullscreen" : "windowed");

		auto Terminate = [this]
		{
			if (m_Handle)
			{
				glfwDestroyWindow(m_Handle);
			}
			if (s_WindowCount == 0)
			{
				glfwTerminate();
			}
		};

		if (s_WindowCount == 0)
		{
			if (!glfwInit())
			{
				const char* errorDesc{};
				int errorCode = glfwGetError(&errorDesc);

				CL_CORE_ERROR("Couldn't create window due to GLFW initialization error: {0}\n\n(GLFW Error Code: {1:x})", errorDesc, errorCode);
				return false;
			}
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		#ifdef CL_TEST_BUILD
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif
			break;
		}
		}
		glfwWindowHint(GLFW_RESIZABLE, m_Data.Resizable);

		GLFWmonitor* monitor = m_Data.Fullscreen ? glfwGetPrimaryMonitor() : nullptr;
		m_Handle = glfwCreateWindow(
			m_Data.Width,
			m_Data.Height,
			m_Data.Title.data(),
			monitor,
			nullptr
		);

		if (!m_Handle)
		{
			CL_CORE_ERROR("Couldn't create window due to glfwCreateWindow returning a NULL window handle!");
			Terminate();
			return false;
		}

		m_Context = GraphicsContext::New(m_Handle);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Handle, &m_Data);
		SetVSync(m_Data.VSync); // actually set it (we never set this yet)

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			WindowCloseEvent e;
			data.Callback(e);

			data.SigClose.Broadcast();
		});

		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.Callback(e);

			data.SigResize.Broadcast(width, height);
		});

		glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow* window, int focused)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			if (focused)
			{
				WindowFocusEvent e;
				data.Callback(e);
				data.SigFocus.Broadcast();
			}
			else
			{
				WindowLoseFocusEvent e;
				data.Callback(e);
				data.SigLoseFocus.Broadcast();
			}
		});

		glfwSetWindowPosCallback(m_Handle, [](GLFWwindow* window, int posX, int posY)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			WindowMoveEvent e(posX, posY);
			data.Callback(e);

			data.SigMove.Broadcast(posX, posY);
		});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			case GLFW_REPEAT:
			{
				KeyPressEvent e((KeyCode) key, action == GLFW_REPEAT);
				data.Callback(e);

				data.SigKeyPress.Broadcast((KeyCode) key, e.IsRepeat());
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleaseEvent e((KeyCode) key);
				data.Callback(e);

				data.SigKeyRelease.Broadcast((KeyCode) key);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressEvent e((MouseCode) button);
				data.Callback(e);

				data.SigMouseButtonPress.Broadcast((MouseCode) button);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent e((MouseCode) button);
				data.Callback(e);

				data.SigMouseButtonRelease.Broadcast((MouseCode) button);
				break;
			}
			}
		});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double posX, double posY)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			MouseMoveEvent e((float) posX, (float) posY);
			data.Callback(e);

			data.SigMouseMove((float) posX, (float) posY);
		});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double offsetX, double offsetY)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			MouseMoveEvent e((float) offsetX, (float) offsetY);
			data.Callback(e);

			data.SigMouseMove((float) offsetX, (float) offsetY);
		});

		CL_CORE_TRACE("Window creation successful.");
		s_WindowCount++;
		return true;
	}

	void DesktopWindow::Update()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	bool DesktopWindow::Destroy()
	{
		if (m_Handle && !glfwWindowShouldClose(m_Handle))
		{
			glfwDestroyWindow(m_Handle);
			m_Handle = nullptr;

			if (--s_WindowCount == 0)
			{
				glfwTerminate();
			}

			return true;
		}
		return false;
	}

	void DesktopWindow::RequestAttention()
	{
		glfwRequestWindowAttention(m_Handle);
	}

	void DesktopWindow::Maximize()
	{
		glfwMaximizeWindow(m_Handle);
	}

	void DesktopWindow::Focus()
	{
		glfwFocusWindow(m_Handle);
	}

	void DesktopWindow::SetTitle(std::string_view title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Handle, title.data());
	}

	void DesktopWindow::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_Handle, width, height);
	}

	void DesktopWindow::SetWidth(int width)
	{
		SetSize(width, m_Data.Height);
	}

	void DesktopWindow::SetHeight(int height)
	{
		SetSize(m_Data.Width, height);
	}

	void DesktopWindow::SetVSync(bool vSync)
	{
		m_Data.VSync = vSync;
		glfwSwapInterval(vSync ? 1 : 0);
	}

	void DesktopWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}

	bool DesktopWindow::HasFocus() const
	{
		int focused{};
		glfwGetWindowAttrib(m_Handle, GLFW_FOCUSED);
		return focused;
	}

	bool DesktopWindow::IsIconified() const
	{
		int focused{};
		glfwGetWindowAttrib(m_Handle, GLFW_ICONIFIED);
		return focused;
	}

	bool DesktopWindow::IsMaximized() const
	{
		int focused{};
		glfwGetWindowAttrib(m_Handle, GLFW_MAXIMIZED);
		return focused;
	}
}
