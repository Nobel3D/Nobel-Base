#pragma once

#include <def.h>
#include "NString.h"

NL_NAMESTART
		class Time
		{
		private:
			int second;
			int Minute;
			int Hour;
			int Day;
			int Month;
			int Year;

			int daysOnMonth(int _Month);
			Time& addDate(const Time* addme);

		public:
			/*NOW TIME*/
			Time();
			Time(int _Day, int _Month, int _Year);
			Time(int _second, int _Minute, int _Hour, int _Day, int _Month, int _Year);

			static NString& NowTime();

			void addSecond(int addme);
			void addMinute(int addme);
			void addHour(int addme);
			void addDay(int addme);
			void addMonth(int addme);
			void addYear(int addme);

			int getSecond();
			int getMinute();
			int getHour();
			int getDay();
			int getMonth();
			int getYear();

			Time& operator+ (Time date_arg);
		};
NL_NAMECLOSE
