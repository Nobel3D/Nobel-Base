#include "NString.h"
#include <Math/Math.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdint>
#include <ctype.h>

using namespace NobelLib;

NString::NString()
{
	memData = new Memory(NL_EMPTY, 1 , 1);
}


NString::NString(const char& str)
{
    newString(str);
}

NString::NString(const byte* str)
{
    newString(str);
}
NString::NString(const char* str)
{
    newString((byte*)str);
}

NString::NString(const NString& _copy)
{
	newString(_copy);
}

NString::NString(const Memory& _copy)
{
    newString(_copy);
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

void NString::newString(const byte* data)
{
    if(memData != nullptr)
        Delete();
    memData = new Memory(data,1, byteSize(data) + 1);
}

void NString::newString(const byte* data, INDEX _index)
{
    if(memData != nullptr)
        Delete();
    memData = new Memory(data,1, _index + 1);
    memData->Write(NL_EMPTY, _index);
}

void NString::newString(const NString& data)
{
    if(memData != nullptr)
        Delete();
    memData = new Memory(*data.memData);
}

void NString::newString(const Memory& data)
{
    if(memData != nullptr)
        Delete();
    memData = new Memory(data.getPointer(), 1, data.getSize());
    memData->Write(NL_EMPTY, data.getSize() - 1);
}

void NString::newString(const byte& data)
{
    if(memData != nullptr)
        Delete();

    byte tmp[] = {data, '\0'};
    memData = new Memory(tmp,1, 2);
}
void NString::addString(const byte* add)
{
    INDEX addLength = byteSize(add);
    INDEX oldLength = memData->getSize();
	memData->Reallocate(oldLength + addLength);

    memData->Write(add, oldLength - 1, addLength + 1);

}

void NString::addString(const byte& add)
{
    INDEX oldLength = memData->getSize();
	memData->Reallocate(oldLength + 1);

    memData->Write(&add, oldLength - 1, 1);
    memData->Write(NL_EMPTY, oldLength, 1);
}


void NString::addString(const NString &add)
{
    INDEX oldLength = memData->getSize();
	memData->Reallocate(oldLength + add.getLength());

    memData->Write(add.memData->getPointer(), oldLength - 1, add.getLength() + 1);
}

void NString::Delete()
{

    memData->Free();
}

void NString::Clear()
{
    memData->Zero();
}
bool NString::Null() const
{
	return *(byte*)memData->Read(0) == '\0';
}

bool NString::Null(const char* IsEmpty)
{
	return IsEmpty == "";
}
byte* NString::Zero()
{
	return NL_EMPTY;
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
	for(int i=0; i<getLength();i++)
	{
		if((*this)[i]==(*str_My)[0])
	{
		for(c; c < str_My->getLength();c++)
			if((*str_My)[c]!=(*this)[i+c])
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

	for(int i=0; i < getLength();i++)
	{
        if((*this)[i]==charMy[0])
        {
            for(c; c<lengthof;c++)
                if(charMy[c]!=(*this)[i+c])
                    break;
            return c == lengthof;
        }
	}
}

NString& NString::Normalize() const
{
    NString* strOffset = new NString(*this);
	strOffset->Replace(NL_ENDLINE, (char*)NL_EMPTY);
	return *strOffset;
}

NString NString::Trim() const
{
    if(Null())
        return *this;

    int c = 0;
    int i = getLength();

	while ((*this)[c] == ' ')
		c++;

	for (i; i >= c; i--)
		if ((*this)[i] != ' ')
			break;

    if(i == c)
    {
        return NString();
    }

    int strlen = i - c + 1;
	return *this;
}

NString& NString::Replace(const char* strNative, const char* strReplace) const
{
	NString* strOutput = new NString(*this);
	for (int i = 0; i < strOutput->getLength();i++)
	if ((*strOutput)[i]==strNative[0])
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
	return atof(*this);
}

int NString::toInt()
{
	return atoi(*this);
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

NString& NString::Sub(INDEX _index) const
{
    NString* strOffset = new NString;

    if (_index < 0 || _index >= getLength())
        return *strOffset;

    //TODO: Seems useless declaration...

    strOffset->newString((byte*)memData->Read(_index, (getLength() + 1) - _index));
	return *strOffset;
}

NString& NString::Sub(char _start) const
{
    NString* strOffset = new NString;

    int iIndex = -1;

    for(int i = 0; i < getLength(); i++)
        if((*this)[i] == _start)
        {
            iIndex = i + 1;
            break;
        }
    if(iIndex == -1)
        return *strOffset;

    //TODO: Seems useless declaration...

    strOffset->newString((byte*)memData->Read(iIndex, getLength() - iIndex));
    return *strOffset;
}

NString& NString::Sub(INDEX _index, INDEX _length) const
{
    NString* strOffset = new NString;
    if(_index > this->getLength() || _index < 0)
        return *strOffset;

    strOffset->newString((byte*)memData->Read(_index, _length), _length);

	return *strOffset;
}


List<NString>* NString::Split(const char* Splitter) const
{
    List<NString>* output = new List<NString>;
	int c = 0;
	int lenSplit = byteSize(Splitter);

	for(int i=0; i < getLength();i++)
	{
		if((*this)[i] == Splitter[0])
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

	for(int i=0; i < getLength();i++)
		if((*this)[i] == Splitter)
        {
            output->addItem(strOutput->Sub(c,i));
            c = i+1;
        }
    output->addItem(this->Sub(c));

    return output;
}


NString& NString::Cut(const char Splitter)
{
    NString* strOutput = new NString;
    for(int i = 0; i < getLength(); i++)
    {
        if((*this)[i] == Splitter)
        {
            *strOutput = Cut(i);
            break;
        }
    }

    return *strOutput;
}

NString& NString::Cut(int length)
{
    if(length > getLength())
        return *this;

    Memory* memOut = new Memory(this->memData->getPointer(), 1, length + 1);

    memOut->Write(NL_EMPTY, length + 1);

    NString* strOutput = new NString(*memOut);

    return *strOutput;
}
NString& NString::toLower() const
{
  NString* strOutput = new NString(*this);

  for (int i=0; i < strOutput->getLength(); i++)
     strOutput->setChar(i,tolower((*this)[i]));

  return *strOutput;
}
NString& NString::toUpper() const
{
  NString* strOutput = new NString(*this);

  for (int i=0; i < strOutput->getLength(); i++)
     strOutput->setChar(i, toupper((*this)[i]));

  return *strOutput;
}

NString& NString::toReverse() const
{
    NString* strOutput = new NString(*this);
    int tempLength = this->getLength();
    int tempCounter = 0;

    for (tempCounter; tempCounter < strOutput->getLength(); tempCounter++)
    {
        strOutput->setChar(tempCounter, (*strOutput)[tempLength]);
        tempLength--;
    }
  strOutput->setChar(tempCounter+1, '\0');

  return *strOutput;
}

NString::operator char *()
{
  return (char*)memData->getPointer();
}

NString::operator const char *() const
{
  return (char*)memData->getPointer();
}

NString& NString::operator =(const char* newChar)
{
	newString((byte*)newChar);
	return *this;
}

NString& NString::operator =(const char& newChar)
{
	this->newString((byte*)&newChar);
	return *this;
}

NString& NString::operator =(const NString& strCopy)
{
	newString(strCopy);
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


char NString::operator[](INDEX _index)
{
	ASSERT(_index >= 0 && _index <= getLength())
	return *(char*)(*memData)[_index];

}

bool NString::Equal(const char* charCompare)
{
    NString strCompare(charCompare);

    return *memData == *strCompare.memData;
}

bool NString::Equal(const NString& strCompare)
{
    return *memData == *strCompare.memData;
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


INDEX NString::getLength() const { return memData->getSize() - 1; }
void NString::setChar(INDEX _index, char _char)
{
    ASSERT(_index >= 0 && _index <= getLength())
	*(char*)(*memData)[_index] = _char;
}
