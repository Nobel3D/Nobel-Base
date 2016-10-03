#pragma once

#include <def.h>
#include <Data/Time.h>

NL_NAMESTART

    class Log
    {
    public:
        Log(const NString& path);
        ~Log();
        NString Add(const NString& handler, const NString& text);
        static NString Add(const NString& handler, const NString& text, const NString& path);
    private:
        NString txt_sLog;
    };

NL_NAMECLOSE
