#pragma once
#include <def.h>
#include <Data/NString.h>

namespace NobelLib
{
    enum LogMode {Quite,MessageBox,Network,Console, All};
    class NException
    {
        private:
            NString ex_sHandler;
            NString ex_sExpression;
            NString ex_sDescription;
            NString ex_sInfo;
            void* ex_vPointer;
        public:
            NException(NString handler, NString expression, NString description, NString info, void* badpointer);
            NException(NString handler, NString expression, NString description, NString info);
            void Notify(LogMode mode);
            void ForceExit();
            virtual ~NException();
    };
}
