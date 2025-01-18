#include "EnginePCH.h"
#include "Application.h"

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
