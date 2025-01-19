#pragma once

#include "Utils/PlatformUtils.h"

namespace Color
{
	class WindowsPlatformUtils : public NativePlatformUtils
	{
	public:
		virtual Timepoint GetLocalTimepoint() const override;
	};
}
