#include "Core/Base.h"

int EntryPoint(int argc, char** argv)
{
	return 0;
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
	return EntryPoint(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return EntryPoint(argc, argv);
}

#endif
