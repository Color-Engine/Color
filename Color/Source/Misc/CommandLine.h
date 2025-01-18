#pragma once

namespace Color
{
	struct CommandLineArgs
	{
		char** List = nullptr;
		int Size = 0;

		CommandLineArgs() = default;
		CommandLineArgs(char** list, int size);

		bool Contains(const char* arg) const;
		int Find(const char* arg) const;
		int Count(const char* arg) const;
	};
}
