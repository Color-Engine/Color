#pragma once

#include "Core/Base.h"

#include <string_view>
#include <string>

namespace Color
{
	class NativeFileSystem
	{
	public:
		virtual ~NativeFileSystem() = default;
		
		virtual bool SetWorkingDir(std::string_view path) = 0;
		virtual std::string GetWorkingDir() const = 0;
		
		virtual bool IsValidEntry(std::string_view path) const = 0;
		virtual bool IsDir(std::string_view path) const = 0;
		virtual bool IsFile(std::string_view path) const = 0;

		virtual std::string Abs(std::string_view path) const = 0;
		virtual std::string Rel(std::string_view path, std::string_view pathRelativeTo) const = 0;
	};

	class FileSystem
	{
	public:
		static bool SetWorkingDir(std::string_view path)
		{
			return s_NativeFS->SetWorkingDir(path);
		}
		
		static std::string GetWorkingDir()
		{
			return s_NativeFS->GetWorkingDir();
		}

		static bool IsValidEntry(std::string_view path)
		{
			return s_NativeFS->IsValidEntry(path);
		}

		static bool IsDir(std::string_view path)
		{
			return s_NativeFS->IsDir(path);
		}

		static bool IsFile(std::string_view path)
		{
			return s_NativeFS->IsFile(path);
		}

		static std::string Abs(std::string_view path)
		{
			return s_NativeFS->Abs(path);
		}

		static std::string Rel(std::string_view path, std::string_view pathRelativeTo)
		{
			return s_NativeFS->Rel(path, pathRelativeTo);
		}

		static std::string Rel(std::string_view path)
		{
			return Rel(path, GetWorkingDir());
		}
	private:
		static Scope<NativeFileSystem> s_NativeFS;
	};
}
