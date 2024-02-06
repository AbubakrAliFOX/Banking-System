#pragma once
#include <ctime>
#include <vector>
#include <iomanip>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 2000;

public:
    // constructors
    clsDate()
    {
        time_t t = time(0);
        tm now;
        localtime_s(&now, &t);
        _Year = now.tm_year + 1900;
        _Month = now.tm_mon + 1;
        _Day = now.tm_mday;
    }

    clsDate(string DateString)
    {
        vector<string> vDate = clsString::Split(DateString, "/");
        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DayFromYearBeginning, short Year)
    {
        clsDate newDate = DateFromYearBegnning(Year, DayFromYearBeginning);
        _Day = newDate._Day;
        _Month = newDate._Month;
        _Year = newDate._Year;
    }

    void SetDay(short Day) { _Day = Day; }

    short GetDay() { return _Day; }

    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short Month) { _Month = Month; }

    short GetMonth() { return _Month; }

    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year) { _Year = Year; }

    short GetYear() { return _Year; }

    __declspec(property(get = GetYear, put = SetYear)) short Year;

    static clsDate GetSysDate()
    {
        clsDate CurrentDate;
        time_t t = time(0);
        tm now;
        localtime_s(&now, &t);
        CurrentDate.Year = now.tm_year + 1900;
        CurrentDate.Month = now.tm_mon + 1;
        CurrentDate.Day = now.tm_mday;
        return CurrentDate;
    }

    string DateToString(clsDate NewDate)
    {
        return to_string(NewDate.Day) + "/" + to_string(NewDate.Month) + "/" + to_string(NewDate.Year);
    }

    static bool IsLeapYear(short Number)
    {
        return (Number % 4 == 0 && Number % 100 != 0) || (Number % 400 == 0);
    }

    static short DaysInMonth(short Year, short Month)
    {
        int DaysOfMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month < 1 || Month > 12) ? 0 : (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (DaysOfMonths[Month - 1]));

        // In One Line:
        // return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
    }

    static short DaysInMonth(clsDate NewDate)
    {
        short Month = NewDate.Month;
        short Day = NewDate.Day;
        short Year = NewDate.Year;

        int DaysOfMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month < 1 || Month > 12) ? 0 : (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (DaysOfMonths[Month - 1]));

        // In One Line:
        // return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11) ? 30 : 31;
    }

    clsDate DateFromYearBegnning(short Year, short Day)
    {
        clsDate NewDate;
        short Month = 1;
        while (true)
        {
            if (Day <= DaysInMonth(Year, Month))
            {
                break;
            }
            Day -= DaysInMonth(Year, Month);
            Month++;
        }

        NewDate.Day = Day;
        NewDate.Year = Year;
        NewDate.Month = Month;
        return NewDate;
    }

    static short OrderOfDate(short Year, short Month, short Day)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2; // Gregorian://0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    static short OrderOfDate(clsDate NewDate)
    {
        return OrderOfDate(NewDate.Year, NewDate.Month, NewDate.Day);
    }

    static string DayShortName(short DayOfWeekOrder)
    {
        string arrDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        return arrDayNames[DayOfWeekOrder];
    }

    static void Print(clsDate NewDate)
    {
        string DateString = to_string(NewDate.Day) + "/" + to_string(NewDate.Month) + "/" + to_string(NewDate.Year);

        cout << "\n\n"
            << DayShortName(OrderOfDate(NewDate)) << ", " << DateString << endl;
    }

    void Print()
    {
        Print(*this);
    }

    static string MonthShortName(short Month)
    {
        string arrDayNames[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
        return arrDayNames[Month - 1];
    }

    static void PrintMonthCalender(short Year, short Month)
    {

        cout << "____________________________________________" << MonthShortName(Month) << "_____________________________________________\n"
            << endl;
        cout << setw(12) << left << "Sun";
        cout << setw(12) << left << "Mon";
        cout << setw(12) << left << "Tue";
        cout << setw(12) << left << "Wed";
        cout << setw(12) << left << "Thu";
        cout << setw(12) << left << "Fri";
        cout << setw(12) << left << "Sat";
        cout << "\n";

        short DaysOfMonth = DaysInMonth(Year, Month);
        short FirstDayOfMonth = OrderOfDate(Year, Month, 1);
        short NumberOfGaps = FirstDayOfMonth;

        short Day = 1;
        short Counter = 0;

        while (Day <= DaysOfMonth)
        {
            string WhatToPrint = NumberOfGaps > 0 ? " " : to_string(Day);
            cout << setw(12) << left << WhatToPrint;
            NumberOfGaps--;
            Counter++;

            if (Counter % 7 == 0)
            {
                cout << endl;
            }

            if (NumberOfGaps < 0)
            {
                Day++;
            }
        }

        cout << "\n____________________________________________________________________________________________" << endl;
    }

    void PrintMonthCalender()
    {
        PrintMonthCalender(this->Year, this->Month);
    }

    static void PrintYearCalender(short Year)
    {
        for (short Month = 1; Month <= 12; Month++)
        {
            PrintMonthCalender(Year, Month);
        }
    }

    void PrintYearCalender()
    {
        PrintYearCalender(this->Year);
    }

    static bool IsValidDate(clsDate NewDate)
    {
        return (NewDate.Month <= 12 && NewDate.Month >= 1) && ((NewDate.Day <= DaysInMonth(NewDate) && NewDate.Day >= 1));
    }

    bool IsValidDate()
    {
        return IsValidDate(*this);
    }

    static bool IsDayLast(clsDate NewDate)
    {
        return NewDate.Day == DaysInMonth(NewDate.Year, NewDate.Month);
    }

    static bool IsMonthLast(clsDate NewDate)
    {
        return NewDate.Month == 12;
    }

    static void AddOneDayToDate(clsDate& NewDate)
    {
        if (IsDayLast(NewDate))
        {
            if (IsMonthLast(NewDate))
            {
                NewDate.Month = 1;
                NewDate.Year++;
            }
            else
            {
                NewDate.Month++;
            }
            NewDate.Day = 1;
        }
        else
        {
            NewDate.Day++;
        }
    }

    static int AgeInDays(clsDate Birthday, bool IncludeEndDay = false)
    {
        clsDate CurrentDate = GetSysDate();

        if (IsDate1BeforeDate2(Birthday, CurrentDate))
        {
            int Counter = 0;
            while (IsDate1BeforeDate2(Birthday, CurrentDate))
            {
                AddOneDayToDate(Birthday);
                Counter++;
            }

            return IncludeEndDay ? ++Counter : Counter;
        }
        else
        {
            return -1;
        }
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? Date1.Day == Date2.Day : false) : (false);
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
    }

    bool IsDate1BeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    bool IsDate1EqualDate2(clsDate Date2)
    {

        return IsDate1EqualDate2(*this, Date2);
    }

    bool IsDate1AfterDate2(clsDate Date2)
    {

        return IsDate1AfterDate2(*this, Date2);
    }

    static enum BeforeAfterEqualDate {
        After = 1,
        Before = -1,
        Equal = 0
    };

    static BeforeAfterEqualDate CompareTwoDates(clsDate Date1, clsDate Date2)
    {
        return IsDate1BeforeDate2(Date1, Date2) ? (BeforeAfterEqualDate::Before) : (IsDate1EqualDate2(Date1, Date2) ? BeforeAfterEqualDate::Equal : BeforeAfterEqualDate::After);
    }

    BeforeAfterEqualDate CompareTwoDates(clsDate Date2)
    {
        return CompareTwoDates(*this, Date2);
    }

    static int CalculateDateDifference(clsDate NewDate1, clsDate NewDate2, bool IncludeEndDay = false)
    {

        if (IsDate1BeforeDate2(NewDate1, NewDate2))
        {
            int Counter = 0;
            while (IsDate1BeforeDate2(NewDate1, NewDate2))
            {
                AddOneDayToDate(NewDate1);
                Counter++;
            }

            return IncludeEndDay ? ++Counter : Counter;
        }
        else
        {
            return -1;
        }
    }

    int CalculateDateDifference(clsDate NewDate2, bool IncludeEndDay = false)
    {

        return CalculateDateDifference(*this, NewDate2, IncludeEndDay);
    }

    static string ReplaceWordInString(string Str, string Item, string Replace)
    {
        short pos = Str.find(Item);
        string Before, After;
        while (pos != std::string::npos)
        {
            Before = Str.substr(0, pos);
            After = Str.substr(pos + Item.length(), Str.length() - 1);
            Str = Before + Replace + After;
            pos = Str.find(Item);
        }
        return Str;
    }

    static string FormateDate(clsDate NewDate, string DateFormat = "dd/mm/yyyy")
    {
        string FormattedDateString = "";
        FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(NewDate.Day));
        FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(NewDate.Month));
        FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(NewDate.Year));
        return FormattedDateString;
    }

    string FormateDate(string DateFormat = "dd/mm/yyyy")
    {
        return FormateDate(*this, DateFormat);
    }

    static void  SwapDates(clsDate& Date1, clsDate& Date2)
    {

        clsDate TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;

    }

};
