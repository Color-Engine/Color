#include "SandboxApp.h"

// -------------------------------------------------------
// >> Entry Point functions defined & implemented here <<
#include "Core/EntryPoint.h"
// -------------------------------------------------------

namespace Sandbox
{
	SandboxApp::SandboxApp(const Color::ApplicationSpecification& specification, const Color::CommandLineArgs& args)
		: Color::Application(specification, args)
	{
	}

	SandboxApp::~SandboxApp()
	{
	}
}

Color::Application* Color::CreateApplicationInstance(const Color::CommandLineArgs& args)
{
	Color::ApplicationSpecification specification;
	specification.Name = "Sandbox";
	specification.WorkingDir = ".";

	return new Sandbox::SandboxApp(specification, args);
}
