#pragma once

#include "Core/Log.h"

#include <limits>

namespace Color
{
	uint64_t Xorshift64(uint64_t& seed);

	class RandomGenerator
	{
	public:
		RandomGenerator() = default;
		RandomGenerator(const RandomGenerator&) = default;
		RandomGenerator& operator=(const RandomGenerator&) = default;
		RandomGenerator(uint64_t seed);

		/**
		 * @brief Creates a random generator whose seed is supplied from the system's local time.
		 */
		static RandomGenerator SeededWithTime(bool xorshiftOnSeedAsWell = true);

		template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
		T Range(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			if (min > max)
			{
				CL_CORE_WARN("RandomGenerator::Range warning! The given minimum range value is greater than the given maximum range value! Swapping min/max values, please check and correct the fed values!");
				std::swap(min, max);
			}
			return Xorshift64(m_Seed) % ((max == std::numeric_limits<T>::max() ? max : max + 1) - min) + min;
		}

		template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
		T Range(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			if (min > max)
			{
				CL_CORE_WARN("RandomGenerator::Range warning! The given minimum range value is greater than the given maximum range value! Swapping min/max values, please check and correct the fed values!");
				std::swap(min, max);
			}
			return min + (Xorshift64(m_Seed) / (float) UINT64_MAX) * (max - min);
		}

		int8_t   Int8  (int8_t  min = INT8_MIN,  int8_t  max = INT8_MAX)  { return Range<int8_t>(min, max); }
		int16_t  Int16 (int16_t min = INT16_MIN, int16_t max = INT16_MAX) { return Range<int16_t>(min, max); }
		int32_t  Int32 (int32_t min = INT32_MIN, int32_t max = INT32_MAX) { return Range<int32_t>(min, max); }
		int64_t  Int64 (int64_t min = INT64_MIN, int64_t max = INT64_MAX) { return Range<int64_t>(min, max); }

		uint8_t  UInt8 (uint8_t  min = 0, uint8_t  max = UINT8_MAX ) { return Range<uint8_t> (min, max); }
		uint16_t UInt16(uint16_t min = 0, uint16_t max = UINT16_MAX) { return Range<uint16_t>(min, max); }
		uint32_t UInt32(uint32_t min = 0, uint32_t max = UINT32_MAX) { return Range<uint32_t>(min, max); }
		uint64_t UInt64(uint64_t min = 0, uint64_t max = UINT64_MAX) { return Range<uint64_t>(min, max); }
		
		float Float(float min = FLT_MIN, float max = FLT_MAX) { return Range<float>(min, max); }
		double Double(double min = DBL_MIN, double max = DBL_MAX) { return Range<double>(min, max); }
		long double LongDouble(long double min = LDBL_MIN, long double max = LDBL_MAX) { return Range<long double>(min, max); }

		/** @brief Given weight must be between 0 and 100. The higher it is, the higher the chance that true will be rolled. */
		bool BoolWithWeight(int weight)
		{
			if (weight < 0 || weight > 100)
			{
				CL_CORE_WARN("RandomGenerator::BoolWithWeight warning, given weight '{}' is not within the range of 0 to 100. The value will be clamped.");
				weight = weight < 0 ? 0 : weight > 100 ? 100 : 0;
			}
			float f = Xorshift64(m_Seed) / (float) UINT64_MAX;
			return f < weight / 100.0f;
		}
		bool Bool() { return UInt64() & 1; }
		
		uint64_t GetSeed() const { return m_Seed; }
	private:
		uint64_t m_Seed = 0;
	};
}
