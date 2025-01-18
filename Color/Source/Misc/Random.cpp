#include "EnginePCH.h"
#include "Random.h"

namespace Color
{
	uint64_t Xorshift64(uint64_t& seed)
	{
		seed ^= seed << 13;
		seed ^= seed >> 7;
		seed ^= seed << 17;
		return seed;
	}

	RandomGenerator::RandomGenerator(uint64_t seed)
		: m_Seed(seed)
	{
	}

	RandomGenerator RandomGenerator::SeededWithTime(bool xorshiftOnSeedAsWell)
	{
		time_t t;
		time(&t);

		uint64_t seed = t;
		if (xorshiftOnSeedAsWell)
		{
			Xorshift64(seed);
		}

		return RandomGenerator(seed);
	}
}
