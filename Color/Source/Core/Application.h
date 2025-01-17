#pragma once

#include "Core/Base.h"
#include "Misc/CommandLine.h"

#include <string>

namespace Color
{
	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDir;
	};
	
	class Application
	{
	public:
		Application(const ApplicationSpecification& specification, const CommandLineArgs& args);
		virtual ~Application();

		void Run();
		void Quit();
		void Exit(int exitcode = 0);

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		const CommandLineArgs& GetArgs() const { return m_Args; }
		bool IsRunning() const { return m_Running; }

		static Application* Get() { return s_Instance; }
	private:
		void CleanUp();
	private:
		ApplicationSpecification m_Specification;
		CommandLineArgs m_Args;

		bool m_Running = false;
	private:
		inline static Application* s_Instance = nullptr;
	};

	// Client must implement if using engine supplied EntryPoint from "Core/EntryPoint.h", which it should use.
	Application* CreateApplicationInstance(const CommandLineArgs& args);
}
