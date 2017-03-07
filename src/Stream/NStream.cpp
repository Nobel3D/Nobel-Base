#include "NStream.h"
#include <Math/Math.h>
#include <stdio.h>

NL_NAMEUSING

NStream::NStream()
{
}

void NStream::WriteLine(const NString& send)
{
    encode_ascii(NString(send + '\n'));
}


NStream& NStream::operator<< (const char* str)
{
    encode_ascii(str);
	return *this;
}

NStream& NStream::operator<< (int value)
{
    encode_int(value);
    return *this;
}

NStream& NStream::operator<<(const NString& str)
{
    encode_ascii(str);
	return *this;
}
NStream& NStream::operator >>(NString& str)
{
    str = ReadLine();
    return *this;
}

NStream& NStream::operator >>(int& value)
{
    value = decode_int();
    return *this;
}

bool NStream::isEoS()
{
    return bEoS;
}

NString NStream::ReadLine()
{
    List<char> data;

    do
    {
        data.addItem(decode_ascii());
    }
    while (*pData != '\n' && !bEoS);

    return NString::fromList(data);
}
NString NStream::ReadAll()
{
    List<char> data;

    do
    {
        data.addItem(decode_ascii());
    }
    while (!bEoS);

    return NString::fromList(data);
}

int NStream::decode_int()
{
    iSize = sizeof(int);
    Read();   
    return Math::byte2int(pData);
}

char NStream::decode_ascii()
{
    iSize = sizeof(char);
    Read();
    return *pData;
}

int NStream::encode_ascii(const char* value)
{
    iSize = sizeof(char);
    pData = new byte(iSize);
    for(int i = 0; i < NString::strSize(value); i++)
    {
        *pData = value[i];
        Write();
    }
    return NL_OK;
}

int NStream::encode_int(int value)
{
    iSize = sizeof(int);
    pData = Math::int2byte(value);
    Write();
    return NL_OK;
}
