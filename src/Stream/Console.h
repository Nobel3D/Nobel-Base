#pragma once

#include <def.h>
#include "NStream.h"

NL_NAMESTART

class Console : public NStream
{
private:
public:
    Console();
    INDEX Read();
    INDEX Write();
};

NL_NAMECLOSE
