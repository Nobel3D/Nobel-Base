#include "NException.h"
#include <stdio.h>

NL_NAMEUSING

NException::NException(NString handler, NString expression, NString description, NString info, void* badpointer)
{
    Log::Add("NBL", "NException badpointer " + NString::fromAddress(badpointer) +" in function {" + handler + "} in this expression {" + expression + "} where " + info + " this is description -> " + description, NL_LOGPATH);
}

NException::NException(NString handler, NString expression, NString description, NString info)
{
    Log::Add("NBL", "NException in function {" + handler + "} in this expression {" + expression + "} where " + info + " this is description -> " + description, NL_LOGPATH);
}

NException::~NException()
{
    //dtor
}

bool NException::Notify(LogMode mode, NString message)
{
    switch (mode)
    {
    case Console:
        printf(message);
        break;
    case Network:
    case MessageBox:
        return false;
    }
    return true;
}
