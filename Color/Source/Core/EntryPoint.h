#pragma once

#include "Core/Application.h"
#include "Scene/Components.h"

namespace Color
{
	int EngineMain(int argc, char** argv)
	{
		// Look at the comment of this function to see why it is called first.
		GenerateComponentIDs();

		Application* application = CreateApplicationInstance({ argv, argc });
		application->Run();

		delete application;
		return 0;
	}
}


#if defined CL_SHIPPING && defined CL_PLATFORM_WINDOWS

#include <Windows.h>

int CALLBACK WinMain
(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR     lpCmdLine,
	_In_     int       nCmdShow
)
{
	return Color::EngineMain(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Color::EngineMain(argc, argv);
}

#endif
