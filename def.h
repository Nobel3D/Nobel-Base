#pragma once

#include <cstddef>

#define NL_NAMESTART namespace NobelLib {
#define NL_NAMECLOSE }
#define NL_NAMEUSING using namespace NobelLib;
#define NL_NAMEIO using namespace NobelLib::IO;

#define NL_LOGPATH "nobel.log"

typedef unsigned char byte;
typedef unsigned int uint;
typedef long long int llint;

template<class Type>
inline Type Max(Type X, Type Y) { return X < Y ? Y : X; }
template<class Type>
inline Type Min(Type X, Type Y) { return X < Y ? X : Y; }
