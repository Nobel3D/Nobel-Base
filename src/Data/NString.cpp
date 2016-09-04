#include "NString.h"
#include <Math/Math.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdint>
#include <ctype.h>

using namespace NobelLib;

byte* NString::str_yEmpty = (byte*)"\0";

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
NString::NString(const NString* CopyCC)
{
	newString(CopyCC->str_yData);
}

NString::~NString()
{
	if (!this->Null())
	{
		delete[] str_yData;
		str_iLength = -1;
	}
}

int NString::byteSize(const byte* array) const
{
    int i = 0;

     while(array[i] != '\0') i++;

    return i;
}

int NString::byteSize(const char* array) const
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
        this->str_yData[i] = data[i];

	this->str_yData[this->str_iLength]= '\0';
}
void NString::newString(const NString& data)
{
    this->Clear();
	this->str_iLength = data.str_iLength;
	this->str_yData = new byte[this->str_iLength + 1];

	int i = data.str_iLength;
    while(i--)
        this->str_yData[i] = data.str_yData[i];

	this->str_yData[data.str_iLength]= '\0';
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

void NString::addString(const char add)
{
	int newLength = this->str_iLength + 2;
	byte* newString = new byte[newLength];

	int i = 0;

	while(i < this->str_iLength)
	{
		newString[i] = this->str_yData[i];
		i++;
	}

	newString[newLength - 1] = add;
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
        this->str_yData = NULL;
}

void NString::Clear()
{
    this->Delete();
    this->newString(this->str_yEmpty);
}
bool NString::Null() const
{
	return this->str_yData == str_yEmpty;
}

bool NString::Null(const char* IsEmpty)
{
	return IsEmpty == "";
}
byte* NString::Zero()
{
	return str_yEmpty;
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
bool NString::Find(const NString* str_My) const
{
	int c=0;
	for(int i=0; i<str_iLength;i++)
	{
		if(str_yData[i]==str_My->str_yData[0])
	{
		for(c; c<str_My->str_iLength;c++)
			if(str_My->str_yData[c]!=this->str_yData[i+c])
				return false;
        return true;
	}
	}
	return false;
}

bool NString::Find(const char* charMy) const
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

NString& NString::Normalize() const
{
    NString* strOffset = new NString(this);
	strOffset->Replace("\n", (char*)str_yEmpty);
	return *strOffset;
}

NString& NString::Trim() const
{
    NString* strOffset = new NString;
    if(Null())
        return *strOffset;

    int c = 0;
    int i = this->str_iLength - 1;

	while (this->str_yData[c] == ' ')
		c++;

	for (i; i >= c; i--)
		if (this->str_yData[i] != ' ')
			break;

    if(i == c)
    {
        return *strOffset;
    }

    int strlen = i - c + 1;
    strOffset->formString(this->str_yData, strlen);
	return *strOffset;
}

NString& NString::Replace(const char* strNative, const char* strReplace) const
{
	NString* strOutput = new NString(this->str_yData);
	for (int i = 0; i < strOutput->str_iLength;i++)
	if (strOutput->str_yData[i]==strNative[0])
	{
		if (strOutput->Sub(i, byteSize(strNative)) == strNative)
		{
			strOutput->newString(strOutput->Sub(0, i) + strReplace + strOutput->Sub( i + byteSize(strNative) ));
		}
	}
	return *strOutput;
}

double NString::toDouble()
{
	return atof((char*)this->str_yData);
}

int NString::toInt()
{
	return atoi((char*)this->str_yData);
}
NString& NString::toBinary(index Decimal)
{
	NString* strOffset = new NString(Math::int2base(Decimal, 2));
	return *strOffset;
}
NString& NString::toHex(index Decimal)
{
    NString* strOffset = new NString(Math::int2base(Decimal, 16));
	return *strOffset;
}
NString& NString::toOct(index Decimal)
{
    NString* strOffset = new NString(Math::int2base(Decimal, 8));
	return *strOffset;
}
NString& NString::fromInt(index IntToString)
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
NString& NString::Sub(int IndexStart) const
{
    NString* strOffset = new NString;
	if (IndexStart<0 || IndexStart>this->getLength())
		return *strOffset;

    strOffset->newString(this->str_yData + IndexStart);
	return *strOffset;
}
NString& NString::Sub(int IndexStart, int IndexLen) const
{
    NString* strOffset = new NString;
    if(IndexStart > this->getLength() || IndexStart < 0)
        return *strOffset;

    strOffset->newString(this->str_yData + IndexStart);

	if(IndexLen > strOffset->getLength())
        return *strOffset;

	strOffset->str_yData[IndexLen] = '\0';
	strOffset->str_iLength = IndexLen;
	return *strOffset;
}


List<NString>* NString::Split(const char* Splitter) const
{
    List<NString>* output = new List<NString>;
	int c = 0;
	int lenSplit = byteSize(Splitter);

	for(int i=0; i<this->str_iLength;i++)
	{
		if(str_yData[i] == Splitter[0])
        {
            if(this->Sub(i,lenSplit)==Splitter)
            {
                output->addItem(this->Sub(c,i));
                c = i+lenSplit;
            }
        }
	}
	output->addItem(this->Sub(c));
    return output;
}

List<NString>* NString::Split(const char Splitter) const
{
    NString* strOutput = new NString(*this);
    List<NString>* output = new List<NString>;

	int c = 0;

	for(int i=0; i<this->str_iLength;i++)
		if(str_yData[i] == Splitter)
        {
            output->addItem(strOutput->Sub(c,i));
            c = i+1;
        }
    output->addItem(this->Sub(c));

    return output;
}

NString& NString::toLower() const
{
  NString* strOutput = new NString(*this);

  for (int i=0; i < strOutput->str_iLength; i++)
     strOutput->str_yData[i] = tolower(strOutput->str_yData[i]);

  return *strOutput;
}
NString& NString::toUpper() const
{
  NString* strOutput = new NString(*this);

  for (int i=0; i < strOutput->str_iLength; i++)
     strOutput->str_yData[i] = toupper(strOutput->str_yData[i]);

  return *strOutput;
}

NString& NString::toReverse() const
{
    NString* strOutput = new NString(*this);
    int tempLength = this->str_iLength;
    int tempCounter = 0;

    for (tempCounter; tempCounter < strOutput->str_iLength; tempCounter++)
    {
        strOutput->str_yData[tempCounter] =  strOutput->str_yData[tempLength];
        tempLength--;
    }
  strOutput->str_yData[tempCounter+1] = '\0';

  return *strOutput;
}

NString::operator const char *()
{
  return (char*)this->str_yData;
}

NString::operator const char *() const
{
  return (char*)this->str_yData;
}

NString& NString::operator =(const char* newChar)
{
	this->Clear();
	newString((byte*)newChar);
	return *this;
}

NString& NString::operator =(char newChar)
{
	this->Clear();
	this->newString((byte*)newChar);
	return *this;
}

NString& NString::operator =(NString& strCopy)
{
	this->Clear();
	newString((byte*)strCopy.str_yData);

	return *this;
}
NString& NString::operator+=(const char addMe)
{
	addString(addMe);
	return *this;
}

NString& NString::operator+=(const char* addMe)
{
	addString((byte*)addMe);
	return *this;
}

NString& NString::operator+=(const NString& addMe)
{
    addString(addMe);
	return *this;
}

NString& NString::operator+(const char* addMe) const
{
    NString* strOffset = new NString(*this);
    strOffset->addString(addMe);
	return *strOffset;
}

NString& NString::operator+(const NString& addMe) const
{
    NString* strOffset = new NString(*this);
    strOffset->addString(addMe);
	return *strOffset;
}

NString& NString::operator+(const char addMe) const
{
    NString* strOffset = new NString(*this);
	strOffset->addString(addMe);
	return *strOffset;
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


index NString::getLength() const { return this->str_iLength; }
byte* NString::getByte() const { return this->str_yData; }
byte* NString::getByte() { return this->str_yData; }
