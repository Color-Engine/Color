#include "EnginePCH.h"
#include "LinuxFileSystem.h"

namespace Color
{
	bool LinuxFileSystem::SetWorkingDir(std::string_view path)
	{
		return chdir(path.data()) == 0;
	}

	std::string LinuxFileSystem::GetWorkingDir() const
	{
		std::string path;
		path.reserve(PATH_MAX);

		if (getcwd(path.data(), PATH_MAX) != 0)
		{
			CL_CORE_ERROR("Error occured while trying to get the current working directory, getcwd() failed!");
			return "";
		}

		return path;
	}
}
