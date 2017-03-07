#include "Math.h"

NL_NAMESTART
namespace Math
{

char mapHex[]{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

INDEX power(INDEX base, INDEX exponent)
{
    INDEX intOffset = 1;
    if(exponent == 0)
        return intOffset;
    for(int i = 0; i < exponent; i++)
        intOffset = intOffset * base;
    return intOffset;
}

char* int2base(INDEX value, INDEX base)
{
    INDEX intExpo = 0;
    INDEX intCheck = 0;
    while(value / power(base,intExpo) > base)
        intExpo++;

    int strLength = intExpo + 2;
    char* strOffset = new char[strLength];

    strLength = 0;
    while(intExpo > -1)
    {
        strOffset[strLength] = mapHex[value / power(base,intExpo)];
        value = value % power(base,intExpo);
        intExpo--;
        strLength++;
    }
    strOffset[strLength] = '\0';
    return strOffset;
}
}


int Math::byte2int(const byte *value)
{
    ASSERT(value != nullptr);
    int out = 0;
    int exp = 0;

    for(int i = sizeof(int); i > 0; i--)
    {
        out += ((int)value[i - 1]) * power(16, exp);
        exp += 2;
    }

    return out;
}

byte* Math::int2byte(int value)
{
    ASSERT(value >= 0);
    byte* out = new byte[sizeof(int)];

    for(int i = sizeof(int); i > 0; i--)
    {

        out[i] = (byte)value % NL_BASE16;
        value /= NL_BASE16;
    }

    return out;
}

NL_NAMECLOSE
