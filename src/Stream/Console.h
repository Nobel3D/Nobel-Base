#pragma once

#include <def.h>
#include "NStream.h"

NL_NAMESTART

    class Console : public NStream
    {
    private:
    public:
        Console();
        INDEX Read(void* vpGet, INDEX length, INDEX count = 1);
        int Write(NString _string);
        int Write(byte* bin, INDEX length);
    };

NL_NAMECLOSE
