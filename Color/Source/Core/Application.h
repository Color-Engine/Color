#pragma once

#include "Core/Window.h"
#include "Core/LayerStack.h"

#include "Event/AppEvent.h"
#include "Misc/CommandLine.h"

#include <string>

namespace Color
{
	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDir;

		WindowSpec WinSpec = { Name };
	};
	
	class Application
	{
	public:
		Application(const ApplicationSpecification& specification, const CommandLineArgs& args);
		virtual ~Application();

		void Run();
		void Quit();
		void Exit(int exitcode = 0);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer, bool deleteObject = true);
		void PopOverlay(Layer* overlay, bool deleteObject = true);

		Window* GetWindow() const { return m_Window.get(); }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		const CommandLineArgs& GetArgs() const { return m_Args; }

		const LayerStack& GetLayerStack() const { return m_LayerStack; }
		bool IsRunning() const { return m_Running; }

		static Application* Get() { return s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void OnEvent(Event& e);
		void CleanUp();
	private:
		Scope<Window> m_Window;

		ApplicationSpecification m_Specification;
		CommandLineArgs m_Args;

		LayerStack m_LayerStack;
		bool m_Running = false;
	private:
		inline static Application* s_Instance = nullptr;
	};

	// Client must implement if using engine supplied EntryPoint from "Core/EntryPoint.h", which it should use.
	Application* CreateApplicationInstance(const CommandLineArgs& args);
}
