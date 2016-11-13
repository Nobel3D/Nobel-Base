#pragma once

#include <cstddef>
#include <assert.h>
#include <stdint-gcc.h>

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
#define NL_EMPTY (byte*)"\0"

typedef unsigned char byte;
typedef unsigned int uint;
typedef int8_t  SHORT;
typedef int32_t INDEX;
typedef int16_t SIZE;
typedef int64_t llint;
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

