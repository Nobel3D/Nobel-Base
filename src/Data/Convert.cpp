#include "Convert.h"
#include <stdio.h>

int Convert::iPrecision = 9;
int Convert::iWidth = 0;

Convert::Convert()
{
}

char* Convert::fFormat()
{
    char format[16];
    char* width = toString(iWidth);
    char* precision = toString(iPrecision);
    int i = 0;
    int x = 0;
    format[i++] = '%';

    while(width[x++] != NL_ZERO)
        format[i++] = width[x];

    x = 0;

    while(precision[x++] != NL_ZERO)
        format[i++] = precision[x];

    format[i++] = 'f';
    format[i] = NL_ZERO;

    return format;
}

int Convert::toInt(const char* str)
{
    int out;
    sscanf(str, "%d", &out);
    return out;
}

float Convert::toFloat(const char* str)
{
    float out;
    sscanf(str, fFormat(), &out);
    return out;
}

double Convert::toDouble(const char* str)
{
    float out;
    sscanf(str, fFormat(), &out);
    return out;
}

char* Convert::toString(const int &value)
{
    char out[64];
    sprintf(out, "%d", value);
    return out;
}

char* Convert::toString(const float &value)
{
    char out[64];
    sprintf(out, fFormat(), value);
    return out;
}

char* Convert::toString(const double &value)
{
    char out[64];
    sprintf(out, fFormat(), value);
    return out;
}

char* Convert::toString(const byte* value)
{

}   //TODO

void Convert::setPrecision(int precision)
{
    if(precision < 0)
        return;
    iPrecision = precision;
}

void Convert::setWidth(int width)
{
    if(width < 0)
        return;
    iWidth = width;
}
