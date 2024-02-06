#pragma once
#include "clsDate.h"

class clsPeriod
{
private:
	clsDate _Start;
	clsDate _End;

public:
	clsPeriod(clsDate Start, clsDate End)
	{
		_Start = Start;
		_End = End;
	}

	void setStart(clsDate Start)
	{
		_Start = Start;
	}

	clsDate getStart()
	{
		return _Start;
	}

	__declspec(property(get = getStart, put = setStart)) clsDate Start;

	clsDate getEnd()
	{
		return _End;
	}

	void setEnd(clsDate End)
	{
		_End = End;
	}

	__declspec(property(get = getEnd, put = setEnd)) clsDate End;

	static bool AreDatesOverLapping(clsPeriod Period1, clsPeriod Period2)
	{
		if (clsDate::CompareTwoDates(Period2.End, Period1.Start) == clsDate::BeforeAfterEqualDate::Before || clsDate::CompareTwoDates(Period2.Start, Period1.End) == clsDate::BeforeAfterEqualDate::After)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool AreDatesOverLapping(clsPeriod Period2)
	{
		return AreDatesOverLapping(*this, Period2);
	}

	static int Length(clsPeriod NewPeriod, bool IncludeEndDay = false)
	{
		return clsDate::CalculateDateDifference(NewPeriod.Start, NewPeriod.End, IncludeEndDay);
	}

	int Length(bool IncludeEndDay = false)
	{
		return Length(*this, IncludeEndDay);
	}

	static bool IsDateWithinPeriod(clsPeriod NewPeriod, clsDate NewDate)
	{
		return !(clsDate::CompareTwoDates(NewDate, NewPeriod.Start) == clsDate::BeforeAfterEqualDate::Before || clsDate::CompareTwoDates(NewDate, NewPeriod.End) == clsDate::BeforeAfterEqualDate::After);
	}

	bool IsDateWithinPeriod(clsDate NewDate)
	{
		return IsDateWithinPeriod(*this, NewDate);
	}


	static int OverlapDays(clsPeriod Period1, clsPeriod Period2)
	{
		if (!AreDatesOverLapping(Period1, Period2))
			return -999;

		int Period1Length = Length(Period1, true);
		int Period2Length = Length(Period2, true);
		int OverlapCounter = 0;

		// for compilation error
		clsDate Period1Start = Period1.Start;
		clsDate Period1End = Period1.End;
		clsDate Period2Start = Period2.Start;
		clsDate Period2End = Period2.End;

		if (Period1Length < Period2Length)
		{
			while (clsDate::IsDateBeforeDate2(Period1Start, Period1End))
			{
				if (IsDateWithinPeriod(Period2, Period1Start))
				{
					OverlapCounter++;
				}
				clsDate::AddOneDayToDate(Period1Start);
			}
		}
		else
		{
			while (clsDate::IsDateBeforeDate2(Period2Start, Period2End))
			{
				if (IsDateWithinPeriod(Period1, Period2Start))
				{
					OverlapCounter++;
				}
				clsDate::AddOneDayToDate(Period2Start);
			}
		}

		return OverlapCounter;
	}

	int OverlapDays(clsPeriod Period2) {
		return OverlapDays(*this, Period2);
	}

};
