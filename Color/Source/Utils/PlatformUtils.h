#pragma once

#include "Core/Base.h"
#include "Misc/Timepoint.h"

namespace Color
{
	class NativePlatformUtils
	{
	public:
		virtual ~NativePlatformUtils() = default;

		virtual Timepoint GetLocalTimepoint() const = 0;
	};

	class PlatformUtils
	{
	public:
		static Timepoint GetLocalTimepoint()
		{
			return s_NativeUtils->GetLocalTimepoint();
		}
	private:
		static Scope<NativePlatformUtils> s_NativeUtils;
	};
}
