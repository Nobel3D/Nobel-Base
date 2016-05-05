#pragma once

#include "Array.h"
#include "def.h"

#define STR_LIMIT 256

namespace NobelLib
{

	class NString
	{
	private:
		NString addString(const char* add);
		NString addString(const char add);
		bool Equal(const char* Compare);
		void newString(const byte* data);
		void formString(const byte* newstr, int& newlen);
		void formString(const NString& copystr);
		int byteSize(const byte* array);
		int byteSize(const char* array);
		Array<NString>& splitString(NString Splitter);

		byte* str_yData;
		int str_iLength;
		static byte* str_yEmpty;


		public:

		~NString();
		NString();
		NString(const char Const);
		NString(const byte* Const);
		NString(const char* Const);
		NString(const NString& CopyCC);

        void Delete();
		void Clear();
		bool Null();
		static bool Null(const char*  IsEmpty);
		static NString Zero();

		bool chk_Number(); //this string is a number?

		Array<NString>& Split(NString& Splitter);
		Array<NString>& Split(const char* Splitter);
		Array<NString>& Split(const char Splitter);
		bool Find(const NString* strMy);
		bool Find(const char* charMy);
		NString Sub(int IndexStart);
		NString Sub(int IndexStart, int IndexLen);

		NString Normalize();
		NString Trim();
		NString Replace(const char* strNative, const char* strReplace);
		NString toLower();
		NString toUpper();
		NString toReverse();
		int toInt();
		double toDouble();
		static NString toHex(int Decimal);
		static NString toBinary(int Decimal);
		static NString fromInt(int IntToString);
		static NString fromDouble(double Convert);

		int getLength();

		operator const char* ();
		operator const char*() const;

		NString operator=(const char* newChar);
		NString operator=(NString& strCopy);
		NString operator=(char newChar);
		NString operator+=(const char* addMe);
		NString operator+=(const char addMe);
		NString operator+=(const NString& addMe);
		NString operator+(const char* addMe);
		NString operator+(const NString& addMe);
		friend NString operator+(char* addMe, NString str)
		{
			return NString(addMe) + str;
		}

		char operator[](int index);

		bool operator==(const char* equal);
		bool operator!=(const char* equal);
		bool operator==(const NString& equal);
		bool operator!=(const NString& equal);
	};
}
