#pragma once

#include <cstddef>
#include <assert.h>

#define NL_NAMESTART namespace NobelLib {
#define NL_NAMECLOSE }
#define NL_NAMEUSING using namespace NobelLib;

#define NL_LOGPATH "nobel.log"
#define NL_STREAMSIZE 1024
#define NL_TIMESTAMP 80

#define NL_OK 1
#define NL_FAIL 0
#define NL_DEBUG 1
#define NL_ENDLINE "\n"


typedef unsigned char byte;
typedef unsigned int uint;
typedef long long int INDEX;
typedef long long int llint;
typedef void* STREAM;

template<class Type>
inline Type Max(Type X, Type Y) { return X < Y ? Y : X; }
template<class Type>
inline Type Min(Type X, Type Y) { return X < Y ? X : Y; }

#define ASSERT(expr) { assert(expr); }

inline int getSize(const byte* array)
{
    int i = 0;
     while(array[i] != '\0') i++;

    return i;
}

