#pragma once

#include "Utils/FileSystem.h"

namespace Color
{
	class WindowsFileSystem : public NativeFileSystem
	{
	public:
		virtual bool SetWorkingDir(std::string_view path) override;
		virtual std::string GetWorkingDir() const override;

		virtual bool IsValidEntry(std::string_view path) const override;
		virtual bool IsDir(std::string_view path) const override;
		virtual bool IsFile(std::string_view path) const override;

		virtual std::string Abs(std::string_view path) const override;
		virtual std::string Rel(std::string_view path, std::string_view pathRelativeTo) const override;
	};
}
