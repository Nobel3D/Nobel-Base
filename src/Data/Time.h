#pragma once

#include <def.h>
#include "NString.h"
#include <ctime>

NL_NAMESTART
		class Time
		{
		public:
			Time();
			Time(time_t epoch);
			Time(int second, int minute, int hour, int day, int month, int year);
			Time(const Time& tm);

			Time& Add(time_t add_epoch);
			Time& Refresh();
			Time& fromHuman(int second, int minute, int hour, int day, int month, int year);
			tm& toHuman();

			NString& Print();
			static NString& Print(time_t epoch);
			static time_t Now();


            int getSecond();
            int getMinute();
            int getHour();
            int getDay();
            int getMonth();
            int getYear();

			Time& operator+ (time_t add_epoch);
			Time& operator- (time_t add_epoch);
			Time& operator+= (time_t add_epoch);
			Time& operator-= (time_t add_epoch);

        private:
			time_t tm_iEpoch = 0;

		};
NL_NAMECLOSE
