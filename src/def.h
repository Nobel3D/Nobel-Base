#pragma once

#include <cstddef>

#define NL_NAMESTART namespace NobelLib {
#define NL_NAMECLOSE }
#define NL_NAMEUSING using namespace NobelLib;

#define NL_LOGPATH "nobel.log"
#define NL_STREAMSIZE 1024
#define NL_TIMESTAMP 80

typedef unsigned char byte;
typedef unsigned int uint;
typedef long long int index;

template<class Type>
inline Type Max(Type X, Type Y) { return X < Y ? Y : X; }
template<class Type>
inline Type Min(Type X, Type Y) { return X < Y ? X : Y; }


inline int getSize(const byte* array)
{
    int i = 0;

     while(array[i] != '\0') i++;

    return i;
}
