#pragma once

#include <def.h>
#include "Data/Time.h"

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

#define STRERR(message) {       fprintf(stderr,message); fprintf(stderr,NL_ENDLINE); }

#define LOG(sector, message, path) {      NobelLib::Log::Add(sector, message, path); \
                                            if(NL_DEBUG) STRERR(message) }

#define NL_LOG(sector, message) { LOG(sector, message, NL_LOGPATH) }
