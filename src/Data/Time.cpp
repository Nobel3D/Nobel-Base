#include "Time.h"

NL_NAMEUSING


Time::Time()
{
    Refresh();
}
Time::Time(time_t epoch)
{
    tm_iEpoch = epoch;
}
Time::Time(int second, int minute, int hour, int day, int month, int year)
{
    fromHuman(second,minute,hour,day,month,year);
}

Time::Time(const Time& tm)
{
    tm_iEpoch = tm.tm_iEpoch;
}

Time& Time::Add(time_t add_epoch)
{
    tm_iEpoch += add_epoch;
	return *this;
}

time_t Time::Now()
{
    return time(0); // get time now
}

Time& Time::Refresh()
{
    tm_iEpoch = Now();
    return *this;
}

Time& Time::fromHuman(int second, int minute, int hour, int day, int month, int year)
{
    struct tm t;
    t.tm_year = year-1900;
    t.tm_mon = month;         // Month, 0 - jan
    t.tm_mday = day;          // Day of the month
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    t.tm_isdst = -1;          // Is DST on? 1 = yes, 0 = no, -1 = unknown
    tm_iEpoch = mktime(&t);
}

tm& Time::toHuman()
{
    return *localtime(&tm_iEpoch);
}

NString& Time::Print()
{
    struct tm t = toHuman();

    char buffer[NL_TIMESTAMP];

    strftime(buffer, NL_TIMESTAMP, "%a %Y-%m-%d %H:%M:%S %Z", &t);

    NString* strOffset = new NString(buffer);

    return *strOffset;
}
NString& Time::Print(time_t epoch)
{
    struct tm t = *localtime(&epoch);

    char buffer[NL_TIMESTAMP];

    strftime(buffer, NL_TIMESTAMP, "%a %Y-%m-%d %H:%M:%S %Z", &t);

    NString* strOffset = new NString(buffer);

    return *strOffset;
}

Time& Time::operator+(time_t add_epoch)
{
    Time* tmOffset = new Time(*this);
    tmOffset->Add(add_epoch);
	return *tmOffset;
}
Time& Time::operator-(time_t add_epoch)
{
    Time* tmOffset = new Time(*this);
    tmOffset->Add(-add_epoch);
	return *tmOffset;
}
Time& Time::operator+=(time_t add_epoch)
{
	return Add(-add_epoch);
}
Time& Time::operator-=(time_t add_epoch)
{
	return Add(add_epoch);
}


int Time::getSecond() { return toHuman().tm_sec; }
int Time::getMinute() { return toHuman().tm_min; }
int Time::getHour()   { return toHuman().tm_hour; }
int Time::getDay()    { return toHuman().tm_mday; }
int Time::getMonth()  { return toHuman().tm_mon; }
int Time::getYear()   { return toHuman().tm_year + 1900; }
