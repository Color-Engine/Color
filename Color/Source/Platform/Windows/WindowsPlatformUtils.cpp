#include "EnginePCH.h"
#include "WindowsPlatformUtils.h"

namespace Color
{
	static Timepoint SystemTimeToTimepoint(SYSTEMTIME st)
	{
		Timepoint tp;
		tp.Year         = (int) st.wYear;
		tp.Month        = (int) st.wMonth;
		tp.DayOfWeek    = (int) st.wDayOfWeek;
		tp.Day          = (int) st.wDay;
		tp.Hour         = (int) st.wHour;
		tp.Minute       = (int) st.wMinute;
		tp.Second       = (int) st.wSecond;
		tp.Second       = (int) st.wMilliseconds;
		tp.Milliseconds = (int) st.wMilliseconds;
		return tp;
	}

	Timepoint WindowsPlatformUtils::GetLocalTimepoint() const
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		return SystemTimeToTimepoint(st);
	}
}
