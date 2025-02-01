#include "EnginePCH.h"
#include "Application.h"

#include "Utils/PlatformUtils.h"
#include "Utils/FileSystem.h"

namespace Color
{
	Application::Application(const ApplicationSpecification& specification, const CommandLineArgs& args)
		: m_Specification(specification), m_Args(args)
	{
		CL_CORE_ASSERT(!s_Instance, "An application instance already exists!");
		s_Instance = this;

		Log::Init();
		CL_CORE_INFO("Initialized logging.");

		CL_CORE_INFO("Engine Build Info:");
		CL_CORE_INFO("  Compiler         -> {} ({})", c_CompilerInfo.Name, c_CompilerInfo.Abbreviation);
		CL_CORE_INFO("  Compilation Date -> {}", __DATE__);
		CL_CORE_INFO("  Compilation Time -> {}", __TIME__);
		CL_CORE_INFO("  Platform         -> {}-{}", CL_PLATFORM_NAME_STRING, ArchitectureToString(c_Architecture));

		if (FileSystem::IsDir(specification.WorkingDir))
		{
			std::string wdir = FileSystem::GetWorkingDir();
			std::string abs = FileSystem::Abs(specification.WorkingDir);

			if (wdir != abs)
			{
				CL_CORE_TRACE("Application specification specified a different working directory than the current one.");
				CL_CORE_TRACE("  Current Working Directory   -> {}", wdir);
				CL_CORE_TRACE("  Requested Working Directory -> {}", abs);
				
				if (FileSystem::SetWorkingDir(abs))
				{
					CL_CORE_INFO("Successfully changed the working directory to '{}'.", FileSystem::GetWorkingDir());
				}
				else
				{
					CL_CORE_ERROR("Change of the working directory failed!");
				}
			}
		}

		m_Window = Window::New(specification.WinSpec);
		if (!m_Window->Create())
		{
			CL_CORE_FATAL("Main application creation failure, Window::Create returned false!");
		}
		m_Window->SetEventCallback(CL_BIND_METHOD(OnEvent));
	}

	Application::~Application()
	{
		if (this == s_Instance)
			s_Instance = nullptr;
	}

	void Application::Run()
	{
		if (m_Running)
		{
			CL_CORE_WARN("The application is already running yet Run() was called, ignoring request.");
			return;
		}

		m_Running = true;
		while (m_Running)
		{
			// TODO: Actually calculate it
			Timestep ts = 0.0f;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(ts);
			}

			m_Window->Update();
		}

		CleanUp();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		Quit();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowCloseEvent>(CL_BIND_METHOD(OnWindowClose));
		Dispatcher.Dispatch<WindowResizeEvent>(CL_BIND_METHOD(OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
			{
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void Application::CleanUp()
	{
		CL_CORE_TRACE("Application clean-up process initiated.");

		while (!m_LayerStack.GetLayers().empty())
		{
			m_LayerStack.PopAll();
		}

		m_Window->Destroy();
		CL_CORE_TRACE("Destroyed the main window.");
	}

	void Application::Quit()
	{
		if (!m_Running)
		{
			CL_CORE_WARN("The application is already not running yet Quit() was called, ignoring request.");
			return;
		}

		m_Running = false;
	}

	void Application::Exit(int exitcode)
	{
		std::exit(exitcode);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer, bool deleteObject)
	{
		layer->OnDetach();
		m_LayerStack.PopLayer(layer);
		if (deleteObject)
		{
			delete layer;
		}
	}

	void Application::PopOverlay(Layer* overlay, bool deleteObject)
	{
		overlay->OnDetach();
		m_LayerStack.PopOverlay(overlay);
		if (deleteObject)
		{
			delete overlay;
		}
	}
}
