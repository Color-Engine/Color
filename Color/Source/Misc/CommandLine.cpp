#include "EnginePCH.h"
#include "CommandLine.h"

namespace Color
{
	bool CommandLineArgs::Contains(const char* arg) const
	{
		for (int i = 0; i < Size; i++)
		{
			if (strcmp(List[i], arg) == 0)
				return true;
		}

		return false;
	}

	int CommandLineArgs::Find(const char* arg) const
	{
		for (int i = 0; i < Size; i++)
		{
			if (strcmp(List[i], arg) == 0)
				return i;
		}

		return -1;
	}

	int CommandLineArgs::Count(const char* arg) const
	{
		int counter{};

		for (int i = 0; i < Size; i++)
		{
			if (strcmp(List[i], arg) == 0)
				counter++;
		}

		return counter;
	}
}
