#include "NString.h"
#include <Math/Math.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdint>
#include <ctype.h>

using namespace NobelLib;

NString::NString()
{}

NString::NString(const char _char)
{
    int a = 1;
    newString(&_char, a);
}

NString::NString(const char* _str)
{
    newString(_str, strSize(_str));
}

NString::NString(const NString& _str)
{
    newString(_str.pData, _str.iLength);
}

void NString::newString(const char* _str, INDEX _len)
{
    iLength = _len;
    pData = new char[iLength + 1];

    int i = iLength;
    while(i--)
        pData[i] = _str[i];

    pData[iLength]= NL_ZERO;
}

void NString::Chain(const char* add, INDEX len)
{
    int newLength = iLength + len + 1;
    char* str = new char[newLength];

    int i = 0;

    while(i < iLength)
    {
        str[i] = pData[i];
        i++;
    }

    for (int c = 0; c < len; c++)
        str[i++] = add[c];

    str[newLength] = NL_ZERO;

    delete[] pData;

    iLength = newLength - 1;
    pData = str;
}

void NString::Delete()
{
    delete[] pData;

    iLength = NULL;
    pData = NULL;
}


bool NString::Null() const
{
    return pData[0] == NL_ZERO;
}

bool NString::Null(const char* _str)
{
    return _str[0] == NL_ZERO;
}

char NString::Zero()
{
    return NL_ZERO;
}

bool NString::isNumber()
{
    for (int i = 0;i < getLength(); i++)
    {
        if ((*this)[i] != '0' && (*this)[i] != '1' &&
            (*this)[i] != '2' && (*this)[i] != '3' &&
            (*this)[i] != '4' && (*this)[i] != '5' &&
            (*this)[i] != '6' && (*this)[i] != '7' &&
            (*this)[i] != '8' && (*this)[i] != '9')
                return false;
    }
    return true;
}

INDEX NString::Find(const char* key) const
{
    return strFind(pData, key);
}

void NString::Trim()
{
    size_t size;
    char *end;

    size = strSize(pData);
    if (!size)
        return;

    end = pData + size;
    while (end >= pData && *end == ' ')
        end--;
    *(end + 1) = '\0';

    while (*pData++ == ' ');

    iLength = strSize(pData);
}

void NString::Replace(const char* strNative, const char* strReplace)
{
    int delta;
    char* n1;

    for (int i = 0; i < iLength; i++)
        if (pData[i]==strNative[0])
        {
            if (strCmp(pData + i, strNative) == 0)
            {
                n1 = strCut(pData, i);
                int len = strSize(strNative);
                delta = len - strSize(strReplace);
                n1 = strCat(n1,strReplace);
                n1 = strCat(n1, pData + i + len);
                break;
            }
    }

    delete[] pData;
    iLength = iLength - delta;
    pData = n1;
    return;
}

double NString::toDouble()
{
    return atof((char*)pData);
}

int NString::toInt()
{
    return atoi((char*)pData);
}
NString& NString::toBinary(INDEX Decimal)
{
    NString* strOffset = new NString(Math::int2base(Decimal, 2));
    return *strOffset;
}
NString& NString::toHex(INDEX Decimal)
{
    NString* strOffset = new NString(Math::int2base(Decimal, 16));
    return *strOffset;
}
NString& NString::toOct(INDEX Decimal)
{
    NString* strOffset = new NString(Math::int2base(Decimal, 8));
    return *strOffset;
}
NString& NString::fromInt(INDEX IntToString)
{
    NString* strOffset = new NString(Math::int2base(IntToString, 10));
    return *strOffset;
}
NString& NString::fromBool(bool value)
{
    NString* strOffset = new NString(value ? "true" : "false");
    return *strOffset;
}

NString& NString::fromAddress(void* value)
{
    uintptr_t address = reinterpret_cast<uintptr_t>(value);
    NString* strOffset = new NString("0x" + toHex(address));
    return *strOffset;
}
NString& NString::fromDouble(double Convert)
{
    char buffer[11];
    NString* strOffset = new NString(buffer);
    return *strOffset;
    //TODO
}

Array<NString>& NString::fromArray(char** array, INDEX index)
{
    Array<NString>* out = new Array<NString>(index);
    for(int i = 0; i < index; i++)
        (*out)[i] = array[i];
    return *out;
}

void NString::Sub(INDEX start)
{
    if (start < 1 || start > iLength)
        return;

    pData = strSub(pData, start);
    iLength = iLength - start;
    return;
}
void NString::Sub(INDEX start, INDEX len)
{
    if (start < 1 || len < 1 || start + len > iLength)
        return;

    pData = strSub(pData, start);
    pData = strCut(pData, len);
    iLength = iLength - (start + len);
    return;
}


Array<NString>& NString::Split(const char* sep) const
{
    int index;
    char** array = strSplit(pData, sep, index);
    return fromArray(array,index);
}


void NString::Cut(const char Splitter)
{
    NString* strOutput = new NString;
    for(int i = 0; i < getLength(); i++)
    {
        if(pData[i] == Splitter)
        {
            pData = strCut(pData, i);
            iLength = strSize(pData);
            break;
        }
    }

}

void NString::Cut(INDEX length)
{
    if(length > iLength)
        return;
    pData = strCut(pData, length);
    iLength = strSize(pData);
}

NString& NString::toLower() const
{
  NString* strOutput = new NString(*this);

  for (int i=0; i < strOutput->iLength; i++)
     strOutput->pData[i] = tolower(strOutput->pData[i]);

  return *strOutput;
}
NString& NString::toUpper() const
{
  NString* strOutput = new NString(*this);

  for (int i=0; i < strOutput->iLength; i++)
     strOutput->pData[i] = toupper(strOutput->pData[i]);

  return *strOutput;
}

NString& NString::toReverse() const
{
    NString* strOutput = new NString(*this);
    int tempLength = iLength;
    int tempCounter = 0;

    for (tempCounter; tempCounter < strOutput->iLength; tempCounter++)
    {
        strOutput->pData[tempCounter] =  strOutput->pData[tempLength];
        tempLength--;
    }
  strOutput->pData[tempCounter+1] = '\0';

  return *strOutput;
}

NString::operator char *()
{
  return (char*)pData;
}

NString::operator const char *() const
{
  return (char*)pData;
}

NString& NString::operator =(const char* str)
{
    Delete();
    newString(str, strSize(str));
    return *this;
}

NString& NString::operator =(const char str)
{
    Delete();
    newString(&str, 1);
    return *this;
}

NString& NString::operator =(NString& str)
{
    Delete();
    newString(str.pData, str.iLength);
    return *this;
}
NString& NString::operator+=(const char str)
{
    Chain(&str, 1);
    return *this;
}

NString& NString::operator+=(const char* str)
{
    Chain(str, strSize(str));
    return *this;
}

NString& NString::operator+=(const NString& str)
{
    Chain(str.pData, str.iLength);
    return *this;
}

NString& NString::operator+(const char* str) const
{
    NString* strOffset = new NString(*this);
    strOffset->Chain(str,strSize(str));
    return *strOffset;
}

NString& NString::operator+(const NString& str) const
{
    NString* strOffset = new NString(*this);
    strOffset->Chain(str.pData, str.iLength);
    return *strOffset;
}

NString& NString::operator+(const char str) const
{
    NString* strOffset = new NString(*this);
    strOffset->Chain(&str, 1);
    return *strOffset;
}


char NString::operator[](int INDEX)
{
    if(INDEX>=0 && INDEX<=iLength)
    return pData[INDEX];

}


bool NString::operator ==(const NString& str)
{
    return strCmp(pData, str.pData) == 0;
}

bool NString::operator !=(const NString& str)
{
    return strCmp(pData, str.pData) != 0;
}

bool NString::operator ==(const char* str)
{
    return strCmp(pData, str) == 0;
}
bool NString::operator !=(const char* str)
{
    return strCmp(pData, str) != 0;
}


INDEX NString::getLength() const { return iLength; }


INDEX NString::strSize(const char* array)
{
    if(array == nullptr)
        return -1;
    int i = 0;

    while(array[i] != '\0') i++;

    return i;
}

char* NString::strCut(const char* str, INDEX len)
{
    ASSERT(len > 0 && len <= strSize(str))

    INDEX nl = len + 1;
    char* out = new char[nl];

    for(int i = 0; i < nl; i++)
        out[i] = str[i];

    out[len] = NL_ZERO;

    return out;
}

char* NString::strCpy(char* dest, const char* src, INDEX len)
{
    ASSERT(len > 0 && len <= strSize(src));

    char *tmp = dest;

    while ( len-- )
        *dest++ = *src++;

    return tmp;
}

char* NString::strCat(char* dest, const char* src)
{
    ASSERT(dest != nullptr && src != nullptr);
    char* out = new char[strSize(dest) + strSize(src)];
    char* tmp = out;

    while (*dest != NL_ZERO)
        *out++ = *dest++;
    while (*src != NL_ZERO)
        *out++ = *src++;

    return tmp;
}

char* NString::strSub(const char* str, INDEX len)
{
    ASSERT(str != nullptr && len <= strSize(str));
    const char* entry = str + len;
    int size = strSize(entry) + 1;
    char* tmp = new char[size];
    for(int i = 0; i < size; i++)
        tmp[i] = entry[i];

    return tmp;
}

int NString::strCmp(const char* str1, const char* str2)
{
    ASSERT(str1 != nullptr && str2 != nullptr);
    ASSERT(str1[0] != NL_ZERO && str2[0] != NL_ZERO);
    byte s1, s2;

    while(1)
    {
        s1 = *str1++;
        s2 = *str2++;

        if(!s1 || !s2)
            return 0;
        if(s1 != s2)
            return s1 < s2 ? -1 : 1;
    }
}

int NString::strFind(const char* str, const char* key)
{
    ASSERT(str != nullptr && key != nullptr);

    for(int i=0; i < strSize(str); i++)
    {
        if(str[i] == key[0])
            if(strCmp(str + i, key) == 0)
                return i;
    }
    return -1;
}

int NString::strFindRecursive(const char* str, const char* key)
{
    ASSERT(str != nullptr && key != nullptr);

    int out = 0;
    for(int i=0; i < strSize(str); i++)
    {
        if(str[i] == key[0])
            if(strCmp(str + i, key) == 0)
                out++;
    }

    return out;
}

char** NString::strSplit(const char* str, const char* key, int& index)
{
    ASSERT(str != nullptr && key != nullptr);

    index = strFindRecursive(str,key) + 1;

    if(index == 0)
        return nullptr;

    char** out = new char*[index];
    int c = 0;
    int last = 0;
    int strleng = strSize(str);

    for(int i=0; i < strleng; i++)
    {
        if(str[i] == key[0])
            if(strCmp(str + i, key) == 0)
            {
                out[c] = new char[i];
                strCpy(out[c], str, i);
                out[c][i] = NL_ZERO;
                last = i;
                c++;
            }
    }
    out[c] = new char[strleng - last];
    strCpy(out[c], str + last, strleng - last);
    return out;
}
