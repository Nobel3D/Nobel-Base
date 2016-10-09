#pragma once

#include <Data/NString.h>
#include <def.h>

NL_NAMESTART

		class Float
		{
		private:
			float n;
		public:
			Float(float _n);
			Float(int _n);
			Float(double _n);
			Float(const Float &copy);
			Float();

			NString toString();
			float getNative();
			float getRound(int numberfloat);
			float getDecimal();
			int toInt();

			void operator*=(Float addMe);
			void operator*=(float addMe);
			void operator/=(Float addMe);
			void operator/=(float addMe);
			void operator+=(Float addMe);
			void operator+=(float addMe);
			void operator-=(Float addMe);
			void operator-=(float addMe);
			void operator=(Float addMe);
			void operator=(float addMe);
			Float operator+(Float addMe);
			Float operator+(float addMe);
			Float operator-(Float addMe);
			Float operator-(float addMe);
			Float operator*(Float addMe);
			Float operator*(float addMe);
			Float operator/(Float addMe);
			Float operator/(float addMe);

			bool operator<(Float addMe);
			bool operator<(float addMe);
			bool operator>(Float addMe);
			bool operator>(float addMe);
			bool operator<=(Float addMe);
			bool operator<=(float addMe);
			bool operator>=(Float addMe);
			bool operator>=(float addMe);
			bool operator==(Float addMe);
			bool operator==(float addMe);
		};

NL_NAMECLOSE
