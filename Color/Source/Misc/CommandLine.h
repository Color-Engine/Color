#pragma once

namespace Color
{
	struct CommandLineArgs
	{
		char** List = nullptr;
		int Size = 0;

		CommandLineArgs() = default;
		CommandLineArgs(const CommandLineArgs&) = default;
		CommandLineArgs& operator=(const CommandLineArgs&) = default;
		~CommandLineArgs() = default;

		bool Contains(const char* arg) const;
		int Find(const char* arg) const;
		int Count(const char* arg) const;
	};
}
