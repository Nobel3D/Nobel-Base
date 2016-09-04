#pragma once

#include <def.h>
#include <Data/NString.h>
#include "Log.h"

namespace NobelLib
{
    enum LogMode {MessageBox,Network,Console};
    class NException
    {
        public:

            NString ex_sHandler     = "";
            NString ex_sExpression  = "";
            NString ex_sDescription = "";
            NString ex_sInfo        = "";
            void* ex_vPointer       = nullptr;
            bool ex_bFatal          = false;

            NException(NString handler, NString expression, NString description, NString info, void* badpointer, bool fatal = false);
            NException(NString handler, NString expression, NString description, NString info, bool fatal = false);
            NException(NString handler, NString expression, NString description, bool fatal = false);
            bool Notify(LogMode mode, NString message);
            void ForceExit();
            virtual ~NException();
    };
}
