#include "NString.h"
#include <stdio.h>
#include <cstdlib>
#include <ctype.h>

using namespace NobelLib;

byte* NString::str_yEmpty = (byte*)"";

NString::NString()
{
	str_yData   = str_yEmpty;
	str_iLength = NULL;
}


NString::NString(const char Const)
{
    int a = 1;
    formString((byte*)Const, a);
}

NString::NString(const byte* Const)
{
    newString(Const);
}
NString::NString(const char* Const)
{
    newString((byte*)Const);
}

NString::NString(const NString& CopyCC)
{
	newString(CopyCC.str_yData);
}

NString::~NString()
{
	if (!this->Null())
	{
		delete[] str_yData;
		str_iLength = -1;
	}
}

int NString::byteSize(const byte* array)
{
    int i = 0;

     while(array[i] != '\0') i++;

    return i;
}

int NString::byteSize(const char* array)
{
    int i = 0;

    while(array[i] != '\0') i++;

    return i;
}
void NString::formString(const byte* newstr, int newlen)
{
    this->Clear();
    this->str_yData = (byte*)newstr;
    this->str_iLength = newlen;
}
void NString::formString(const NString& copystr)
{
    this->Clear();
    this->str_yData = copystr.str_yData;
    this->str_iLength = copystr.str_iLength;
}

void NString::newString(const byte* data)
{
	this->str_iLength = byteSize(data);
	this->str_yData = new byte[this->str_iLength + 1];

	int i = this->str_iLength;
    while(i--)
	{
    this->str_yData[i] = data[i];
	}

	this->str_yData[this->str_iLength]= '\0';
}

void NString::addString(const byte* add)
{
    int addLength = byteSize(add);
	int newLength = this->str_iLength + addLength + 1;
	byte* newString = new byte[newLength];

	int i = 0;

	while(i < this->str_iLength)
	{
		newString[i] = this->str_yData[i];
		i++;
	}

	for (int c = 0; c<addLength; c++)
		newString[i++] = add[c];

	newString[newLength] = '\0';

	this->formString(newString,newLength - 1);
}

void NString::addString(const NString &add)
{
	int newLength = this->str_iLength + add.str_iLength + 1;
	byte* newString = new byte[newLength];

	int i = 0;

	while(i < this->str_iLength)
	{
		newString[i] = this->str_yData[i];
		i++;
	}

	for (int c = 0; c<add.str_iLength; c++)
		newString[i++] = add.str_yData[c];

	newString[newLength] = '\0';

	this->formString(newString,newLength - 1);
}
void NString::Delete()
{
    if(!this->Null())
        delete[] this->str_yData;

        this->str_iLength = NULL;
        this->str_yData = str_yEmpty;
}

void NString::Clear()
{
    this->Delete();
    this->newString(this->str_yEmpty);
}
bool NString::Null()
{
	return this->str_yData == str_yEmpty;
}

bool NString::Null(const char* IsEmpty)
{
	return IsEmpty == "";
}

NString NString::Zero()
{
	return NString(str_yEmpty);
}

bool NString::chk_Number()
{
	for (int i = 0;i < this->getLength(); i++)
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
bool NString::Find(const NString* str_My)
{
	int c=0;
	for(int i=0; i<str_iLength;i++)
	{
		if(str_yData[i]==str_My->str_yData[0])
	{
		for(c; c<str_My->str_iLength;c++)
			if(str_My->str_yData[c]!=str_yData[i+c])
				return false;
        return true;
	}
	}
	return false;
}

bool NString::Find(const char* charMy)
{
	int lengthof=byteSize(charMy);
	int c=0;

	for(int i=0; i<this->str_iLength;i++)
	{
        if(str_yData[i]==charMy[0])
        {
            for(c; c<lengthof;c++)
                if(charMy[c]!=this->str_yData[i+c])
                    break;
            return c == lengthof;
        }
	}
}

NString NobelLib::NString::Normalize()
{
	this->Replace("\n", (char*)str_yEmpty);
	return *this;
}

NString NString::Trim()
{
    if(Null())
        return *this;

    int c = 0;
    int i = this->str_iLength - 1;

	while (this->str_yData[c] == ' ')
		c++;

	for (i; i >= c; i--)
		if (this->str_yData[i] != ' ')
			break;

    if(i == c)
        return NString("");

    int strlen = i - c + 1;
    byte* stroffset = new byte[strlen];

    for (int d = 0; d < strlen; d++)
    {
		stroffset[d] = this->str_yData[c];
		c++;
    }
	return NString(stroffset);
}

NString NString::Replace(const char* strNative, const char* strReplace)
{
	NString strChangeble (this->str_yData);
	for (int i = 0; i < this->getLength();i++)
	if (strChangeble[i]==strNative[0])
	{
		if (strChangeble.Sub(i, byteSize(strNative)) == strNative)
		{
			strChangeble = strChangeble.Sub(0, i) + strReplace + strChangeble.Sub( i + byteSize(strNative) );
		}
	}
	return strChangeble;
}

double NString::toDouble()
{
	return atof((char*)this->str_yData);
}

int NString::toInt()
{
	return atoi((char*)this->str_yData);
}
NString NString::toBinary(int Decimal)
{
	char buffer[STR_LIMIT];
	snprintf(buffer,STR_LIMIT, "%b", Decimal);
	return NString(buffer);
}
NString NString::toHex(int Decimal)
{
	char buffer[STR_LIMIT];
	snprintf(buffer,STR_LIMIT,"%h", Decimal);
	return NString(buffer);
}
NString NString::fromInt(int IntToString)
{
	char buffer[STR_LIMIT];
	snprintf(buffer, STR_LIMIT ,"%d", IntToString);
	return NString(buffer);
}
NString NString::fromDouble(double Convert)
{
	char buffer[STR_LIMIT];
	return NString();
	//TODO
}
NString NString::Sub(int IndexStart)
{
	if (IndexStart<0 || IndexStart>this->getLength())
		return *this;
    NString strOffset(this->str_yData + IndexStart);
	return strOffset;
}
NString NString::Sub(int IndexStart, int IndexLen)
{
	NString Exit(this->str_yData+IndexStart);

	if (IndexLen > Exit.getLength())
		return Sub(IndexStart);

	Exit.str_yData[IndexLen] = '\0';
	return Exit;
}

Array<NString>& NString::splitString(NString Splitter)
{
	NString* strSafe = new NString(*this);
	Array<NString> arrayOffset(2);

	int entrypoint = 0;
	int exitpoint = 0;

	int c = 0;

	for(int i=0; i<this->str_iLength;i++)
	{
		if(str_yData[i] == Splitter[0])
        {
            for(c; c < Splitter.getLength(); c++)
                if(Splitter[c] != this->str_yData[i+c])
                    break;
            if(c == Splitter.getLength())
            {
                entrypoint = i;
                exitpoint = i+c;
                break;
            }
        }
	}
	arrayOffset[0] = strSafe->Sub(0,entrypoint);
	arrayOffset[1] = strSafe->Sub(exitpoint);

	return arrayOffset;
}


Array<NString>& NString::Split(NString Splitter)
{
    return this->splitString(Splitter);
}

Array<NString>& NString::Split(const char* Splitter)
{
    return this->splitString(NString(Splitter));
}
Array<NString>& NString::Split(const char Splitter)
{
    return this->splitString(NString(Splitter));
}

NString NString::toLower()
{
  byte* s = this->str_yData;

  while (*s) {
     *s = tolower(*s);
      s++;
  }

  return *this;
}
NString NString::toUpper()
{
	  byte* s = this->str_yData;

  while (*s) {
     *s = toupper(*s);
      s++;
  }

  return *this;
}

NString NString::toReverse()
{
    byte*  s = this->str_yData;
    int    p = this->str_iLength - 1;
    byte*  q = new byte[p + 1];
    int    r = 0;

    //SPQR?

    while (p+1) {
        q[r]  = s[p];
        r++;
        p--;
    }
    q[r] = '\0';

  return NString(q);
}

NString::operator const char *()
{
  return (char*)this->str_yData;
}

NString::operator const char *() const
{
  return (char*)this->str_yData;
}

NString NString::operator =(const char* newChar)
{
	this->Clear();
	newString((byte*)newChar);
	return *this;
}

NString NString::operator =(char newChar)
{
	this->Clear();
	this->newString((byte*)newChar);
	return *this;
}

NString NString::operator =(NString& strCopy)
{
	this->Clear();
	newString((byte*)strCopy.str_yData);

	return *this;
}
NString NString::operator+=(const char addMe)
{
	addString((byte*)addMe);
	return *this;
}

NString NString::operator+=(const char* addMe)
{
	addString((byte*)addMe);
	return *this;
}

NString NString::operator+=(const NString& addMe)
{
    addString(addMe);
	return *this;
}

NString NString::operator+(const char* addMe)
{
    NString offString(*this);
    offString.addString(addMe);
	return offString;
}

NString NString::operator+(const NString& addMe)
{
    NString offString(*this);
    offString.addString(addMe);
	return offString;
}

char NString::operator[](int index)
{
	if(index>=0 && index<=str_iLength)
	return str_yData[index];

}

bool NString::Equal(const char* Compare)
{
	int compareLength = byteSize(Compare);

	if (compareLength == this->str_iLength)
	{
		for (int i = 0; i<compareLength; i++)
            if (Compare[i] != this->str_yData[i])
                return false;
        return true;
	}
	else
		return false;
}

bool NString::operator ==(const NString& equal)
{
	return Equal(equal);
}

bool NString::operator !=(const NString& equal)
{
	return !Equal(equal);
}

bool NString::operator ==(const char* equal)
{
	return Equal(equal);
}
bool NString::operator !=(const char* equal)
{
	return !Equal(equal);
}


int NString::getLength(){ return this->str_iLength; }
