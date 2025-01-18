#include "EnginePCH.h"
#include "ECSID.h"

namespace Color
{
	ECSID GetNextComponentTypeID()
	{
		static ECSID Current = 1; // 0 is reserved for invalid IDs, see INVALID_ECS_ID
		return Current++;
	}
}
