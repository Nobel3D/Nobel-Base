#pragma once

#include <def.h>
#include <Data/Time.h>

NL_NAMESTART

    class Log
    {
    private:
        NString txt_sLog;
    public:
        Log(NString path);
        ~Log();
        NString Add(NString handler, NString text);
        static NString Add(NString handler, NString text, NString path);
    };

NL_NAMECLOSE
