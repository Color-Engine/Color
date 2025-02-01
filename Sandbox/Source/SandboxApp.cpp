#include "SandboxApp.h"

// -------------------------------------------------------
// >> Entry Point functions defined & implemented here <<
#include "Core/EntryPoint.h"
// -------------------------------------------------------

#include "Sandbox2D.h"

namespace Sandbox
{
	SandboxApp::SandboxApp(const Color::ApplicationSpecification& specification, const Color::CommandLineArgs& args)
		: Color::Application(specification, args)
	{
		PushLayer(new Sandbox2D());
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

	specification.WinSpec.Title = specification.Name;
	specification.WinSpec.Width = 1600;
	specification.WinSpec.Height = 900;
	specification.WinSpec.Fullscreen = false;
	specification.WinSpec.Resizable = true;
	specification.WinSpec.VSync = true;

	return new Sandbox::SandboxApp(specification, args);
}
