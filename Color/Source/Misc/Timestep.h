#pragma once

namespace Color
{
	struct Timestep
	{
		float Time = 0.0f;

		Timestep() = default;
		Timestep(const Timestep&) = default;
		Timestep& operator=(const Timestep&) = default;
		Timestep(float time)
			: Time(time) {}

		float GetTime() const { return Time; }
		operator float() const { return Time; }
		float operator()() const { return Time; }
	};
}
