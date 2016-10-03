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

NL_NAMECLOSE
