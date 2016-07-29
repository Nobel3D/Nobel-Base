#pragma once

#include "def.h"
#include <Data/NString.h>
#include <Data/Time.h>
#include <Stream/NFile.h>

NL_NAMESTART
NL_NAMEIO

class Log
{
    private:
        NFile* txt_fLog;
        public:
        Log(NString path);
        ~Log();
        void Add(NString handler, NString text);
        static void Add(NString handler, NString text, NString path);
};

NL_NAMECLOSE
