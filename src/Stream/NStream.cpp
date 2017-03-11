#include "NStream.h"
#include <Math/Math.h>
#include <Data/Convert.h>
#include <stdio.h>

NL_NAMEUSING

NStream::NStream()
{
}

void NStream::WriteLine(const NString& send)
{
    encode_ascii(NString(send + '\n'));
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
     return decode<int>();
}

float NStream::decode_float()
{
     return decode<float>();
}

double NStream::decode_double()
{
     return decode<double>();
}

char NStream::decode_ascii()
{
    return decode<char>();
}

int NStream::encode_int(const int& value)
{
    return encode<int>(value);
}

int NStream::encode_float(const float& value)
{
    return encode<float>(value);
}

int NStream::encode_double(const double& value)
{
    return encode<double>(value);
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

NStream& NStream::operator<< (const char* str)
{
    encode_ascii(str);
    return *this;
}

NStream& NStream::operator<< (const int &value)
{
    encode_int(value);
    return *this;
}
NStream& NStream::operator<<(const NString& str)
{
    encode_ascii(str);
    return *this;
}
NStream& NStream::operator <<(const float &value)
{
    encode_float(value);
    return *this;
}
NStream& NStream::operator <<(const double &value)
{
    encode_double(value);
    return *this;
}
NStream& NStream::operator >>(NString& str)
{
    str = ReadLine();
    return *this;
}

NStream& NStream::operator >>(int &value)
{
    value = decode_int();
    return *this;
}

NStream& NStream::operator >>(float &value)
{
    value = decode_float();
    return *this;
}
NStream& NStream::operator >>(double &value)
{
    value = decode_double();
    return *this;
}
