#pragma once

#include "def.h"

NL_NAMESTART
namespace Math
{
    static char* hexMap;
    INDEX power(INDEX base, INDEX exponent);
    char* int2base(INDEX value, INDEX base);
    char* double2base(INDEX value);
    int byte2int(const byte* value);
    byte* int2byte(int value);
}
NL_NAMECLOSE
