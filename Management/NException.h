#pragma once

#include <def.h>
#include <Data/NString.h>
#include "Log.h"

namespace NobelLib
{
    enum LogMode {MessageBox,Network,Console};
    class NException
    {
        private:
        public:
            NException(NString handler, NString expression, NString description, NString info, void* badpointer);
            NException(NString handler, NString expression, NString description, NString info);
            bool Notify(LogMode mode , NString message);
            void ForceExit();
            virtual ~NException();
    };
}
