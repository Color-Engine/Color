#include "EnginePCH.h"
#include "Application.h"

namespace Color
{
	Application::Application(const ApplicationSpecification& specification, const CommandLineArgs& args)
		: m_Specification(specification), m_Args(args)
	{
		CL_CORE_ASSERT(!s_Instance, "An application instance already exists!");
		s_Instance = this;

		Log::Init();
		CL_CORE_INFO("Initialized logging.");

		// TODO: Switch wdir if specified via appspec
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

		}

		CleanUp();
	}

	void Application::CleanUp()
	{
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
}
