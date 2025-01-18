#include "EnginePCH.h"
#include "WindowsFileSystem.h"

#include <Shlwapi.h>

namespace Color
{
	bool WindowsFileSystem::SetWorkingDir(std::string_view path)
	{
		return SetCurrentDirectoryA(path.data());
	}

	std::string WindowsFileSystem::GetWorkingDir() const
	{
		std::string path;
		path.resize(MAX_PATH);

		DWORD dwWritten = GetCurrentDirectoryA(MAX_PATH, path.data());
		if (dwWritten == 0)
		{
			CL_CORE_ERROR("Error occurred while trying to get the current working directory, GetCurrentDirectoryA() reported zero written characters to the expected buffer!");
			return "";
		}
		path.resize(dwWritten);

		return path;
	}

	bool WindowsFileSystem::IsValidEntry(std::string_view path) const
	{
		DWORD dwAttrib = GetFileAttributesA(path.data());
		return dwAttrib != INVALID_FILE_ATTRIBUTES;
	}

	bool WindowsFileSystem::IsDir(std::string_view path) const
	{
		DWORD dwAttrib = GetFileAttributesA(path.data());
		return dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
	}

	bool WindowsFileSystem::IsFile(std::string_view path) const
	{
		DWORD dwAttrib = GetFileAttributesA(path.data());
		return dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
	}

	std::string WindowsFileSystem::Abs(std::string_view path) const
	{
		std::string result;
		result.resize(MAX_PATH);

		DWORD dwWritten = GetFullPathNameA(path.data(), MAX_PATH, result.data(), NULL);
		if (dwWritten == 0)
		{
			CL_CORE_ERROR("Error occurred while trying to get the absolute path of '{}', GetFullPathNameA() reported zero written characters to the expected buffer!", path);
			return "";
		}
		result.resize(dwWritten);

		return result;
	}

	std::string WindowsFileSystem::Rel(std::string_view path, std::string_view pathRelativeTo) const
	{
		std::string result;
		result.resize(MAX_PATH);

		if (!PathRelativePathToA(result.data(), pathRelativeTo.data(), FILE_ATTRIBUTE_DIRECTORY, path.data(), IsDir(path) ? FILE_ATTRIBUTE_DIRECTORY : NULL))
		{
			CL_CORE_ERROR("Error occurred while trying to get the path '{}' as relative to the path '{}', PathRelativePathToA() returned FALSE!");
			return "";
		}

		for (int i = 0; i < MAX_PATH; i++)
		{
			if (result[i] == '\0')
			{
				result.resize(i+1);
			}
		}

		return result;
	}
}
