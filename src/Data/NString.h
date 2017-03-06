#pragma once

#include "List.h"
#include "Array.h"
#include "def.h"

NL_NAMESTART

	class NString
	{
    private:
        char* pData = nullptr;
        INDEX iLength = 0;

        void Chain(const char*, INDEX);

        void newString(const char*, INDEX);

    public:
        inline NString();
        inline NString(const char);
        inline NString(const char*);
        inline NString(const NString&);

        void Delete();
        bool Null() const;
        static bool Null(const char*);
        static char Zero();

        bool isNumber(); //this string is a number?

        INDEX Find(const char*) const;
        void Replace(const char* strNative, const char* strReplace);
        void Sub(INDEX start);
        void Sub(INDEX start, INDEX len);
        void Cut(INDEX);
        void Cut(const char);
        Array<NString>& Split(const char* Splitter) const;

        void Trim();
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
        static Array<NString>& fromArray(char**, INDEX);

        INDEX getLength() const;

        static INDEX strSize(const char*);
        static char* strCut(const char*, INDEX);
        static char* strCpy(char*, const char*, INDEX);
        static char* strCat(char*, const char*);
        static char* strSub(const char*, INDEX);
        static int strCmp(const char*, const char*);
        static int strFind(const char*, const char*);
        static int strFindRecursive(const char*, const char*);
        static char** strSplit(const char*, const char*, int&);

        operator char* ();
        operator const char*() const;

        NString& operator=(const char* newChar);
        NString& operator=(NString& strCopy);
        NString& operator=(const char str);
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

        char operator[](int INDEX);

        bool operator==(const char* equal);
        bool operator!=(const char* equal);
        bool operator==(const NString& equal);
        bool operator!=(const NString& equal);
	};

NL_NAMECLOSE
