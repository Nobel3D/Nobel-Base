#pragma once

#include "List.h"
#include "Array.h"
#include "Memory.h"
#include "def.h"

NL_NAMESTART

	class NString
	{
    private:
		Memory* memData = nullptr;

		void addString(const byte* add);
		void addString(const NString& add);
		void addString(const byte& add);

        void newString(const byte* data, INDEX _index);
		void newString(const byte* data);
		void newString(const NString& data);
		void newString(const Memory& data);
		void newString(const byte& data);

		bool Equal(const char* charCompare);
		bool Equal(const NString& strCompare);

        int byteSize(const byte* array) const;
		int byteSize(const char* array) const;

    public:
		NString();
		NString(const char& Const);
		NString(const byte* Const);
		NString(const char* Const);
		NString(const NString& _copy);
        NString(const Memory& _copy);


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
		NString& Sub(int INDEXStart) const;
		NString& Sub(int INDEXStart, int INDEXLen) const;

		NString& Normalize() const;
		NString Trim() const;
		NString& Replace(const char* strNative, const char* strReplace) const;
		NString& toLower() const;
		NString& toUpper() const;
		NString& toReverse() const;
		int toInt();
		double toDouble();
		static NString& toHex(INDEX Decimal);
		static NString& toOct(INDEX Decimal);
		static NString& toBinary(INDEX Decimal);
		static NString& fromInt(INDEX IntToString);
		static NString& fromBool(bool value);
		static NString& fromAddress(void* address);
		static NString& fromDouble(double Convert);

		INDEX getLength() const;

		operator char* ();
		operator const char*() const;

		NString& operator=(const char* newChar);
		NString& operator=(const NString& strCopy);
		NString& operator=(const char& newChar);
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

		char operator[](INDEX _index);

		bool operator==(const char* equal);
		bool operator!=(const char* equal);
		bool operator==(const NString& equal);
		bool operator!=(const NString& equal);

		void setChar(INDEX _index, char _char);
	};

NL_NAMECLOSE
