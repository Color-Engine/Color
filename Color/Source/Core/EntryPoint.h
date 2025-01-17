#pragma once

#include "Core/Application.h"

namespace Color
{
	int EntryPoint(int argc, char** argv)
	{
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
	return Color::EntryPoint(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Color::EntryPoint(argc, argv);
}

#endif
