#pragma once

#include "Core/Base.h"

namespace Color
{
	using ECSID = uint64_t;
	inline constexpr ECSID INVALID_ECS_ID = 0;

	ECSID GetNextComponentTypeID();
	template <typename T>
	ECSID GetTypeComponentID()
	{
		static ECSID TypeID = GetNextComponentTypeID();
		return TypeID;
	}
}
