#pragma once

#include <def.h>
#include <Data/Time.h>

NL_NAMESTART

    class Log
    {
    public:
        Log(const NString& path);
        ~Log();
        void Add(const NString& handler, const NString& text);
        static void Add(const NString& handler, const NString& text, const NString& path);
    private:
        NString txt_sLog;
    };

NL_NAMECLOSE
