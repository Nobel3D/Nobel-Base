#pragma once

#include "List.h"
#include "Array.h"
#include "def.h"

namespace NobelLib
{

	class NString
	{
	private:
		void addString(const byte* add);
		void addString(const NString &add);
		void addString(const char add);
		void newString(const byte* data);
		void newString(const NString &data);

		bool Equal(const char* Compare);

        void formString(const byte* newstr, int newlen);
		void formString(const NString& copystr);

        int byteSize(const byte* array) const;
		int byteSize(const char* array) const;

		byte* str_yData;
		index str_iLength;
		static byte* str_yEmpty;

		public:

		inline ~NString();
		inline NString();
		inline NString(const char Const);
		inline NString(const byte* Const);
		inline NString(const char* Const);
		inline NString(const NString& CopyCC);
		inline NString(const NString* CopyCC);



        void Delete();
		void Clear();
		bool Null() const;
		static bool Null(const char*  IsEmpty);
		static byte* Zero();

		bool chk_Number(); //this string is a number?

		List<NString>* Split(const char* Splitter) const;
		List<NString>* Split(const char Splitter) const;
		bool Find(const NString* strMy) const;
		bool Find(const char* charMy) const;
		NString& Sub(int IndexStart) const;
		NString& Sub(int IndexStart, int IndexLen) const;

		NString& Normalize() const;
		NString& Trim() const;
		NString& Replace(const char* strNative, const char* strReplace) const;
		NString& toLower() const;
		NString& toUpper() const;
		NString& toReverse() const;
		int toInt();
		double toDouble();
		static NString& toHex(index Decimal);
		static NString& toOct(index Decimal);
		static NString& toBinary(index Decimal);
		static NString& fromInt(index IntToString);
		static NString& fromBool(bool value);
		static NString& fromAddress(void* address);
		static NString& fromDouble(double Convert);

		index getLength() const;
        byte* getByte();
		byte* getByte() const;

		operator char* ();
		operator const char*() const;

		NString& operator=(const char* newChar);
		NString& operator=(NString& strCopy);
		NString& operator=(char newChar);
		NString& operator+=(const char* addMe);
		NString& operator+=(const char addMe);
		NString& operator+=(const NString& addMe);
		NString& operator+(const char* addMe) const;
		NString& operator+(const NString& addMe) const;
		NString& operator+(const char addMe) const;
		friend NString& operator+(char* addMe, NString str)
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
