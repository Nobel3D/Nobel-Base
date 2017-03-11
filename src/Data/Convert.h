#ifndef CONVERT_H
#define CONVERT_H

#include <def.h>
#include "NString.h"
#include <Math/Math.h>

class Convert
{
private:
    static int iPrecision;
    static int iWidth;

    static char* fFormat();
public:
    Convert();
    static int toInt(const char* str);
    static float toFloat(const char* str);
    static double toDouble(const char* str);
    static char* toString(const int &value);
    static char* toString(const float &value);
    static char* toString(const double &value);
    static char* toString(const byte* value);
    static void setPrecision(int precision);
    static void setWidth(int width);
};

#endif // CONVERT_H
