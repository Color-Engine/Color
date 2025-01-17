#include "EnginePCH.h"
#include "Application.h"

namespace Color
{
	Application::Application(const ApplicationSpecification& specification, const CommandLineArgs& args)
		: m_Specification(specification), m_Args(args)
	{
		// TODO: Assert !s_Instance
		s_Instance = this;

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
		m_Running = false;
	}

	void Application::Exit(int exitcode)
	{
		std::exit(exitcode);
	}
}
