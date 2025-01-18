#pragma once

#include "Utils/FileSystem.h"

namespace Color
{
	class LinuxFileSystem : public NativeFileSystem
	{
	public:
		virtual bool SetWorkingDir(std::string_view path) override;
		virtual std::string GetWorkingDir() const override;
	};
}
