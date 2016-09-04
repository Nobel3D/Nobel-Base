#include "NException.h"
#include <cstdlib> //for exit()

NL_NAMEUSING

NException::NException(NString handler, NString expression, NString description, NString info, void* badpointer, bool fatal)
{
    ex_sHandler     = handler;
    ex_sExpression  = expression;
    ex_sDescription = description;
    ex_sInfo        = info;
    ex_vPointer     = badpointer;
    ex_bFatal       = fatal;

    Log::Add("NBL", "NException badpointer " + NString::fromAddress(badpointer) +" in function {" + handler + "} in this expression {" + expression + "} where " + info + " this is description -> " + description, NL_LOGPATH);
}

NException::NException(NString handler, NString expression, NString description, NString info, bool fatal)
{
    ex_sHandler     = handler;
    ex_sExpression  = expression;
    ex_sDescription = description;
    ex_sInfo        = info;
    ex_bFatal       = fatal;

    Log::Add("NBL", "NException in function {" + handler + "} in this expression {" + expression + "} where " + info + " this is description -> " + description, NL_LOGPATH);
}

NException::NException(NString handler, NString expression, NString description, bool fatal)
{
    ex_sHandler     = handler;
    ex_sExpression  = expression;
    ex_sDescription = description;
    ex_bFatal       = fatal;

    Log::Add("NBL", "NException in function {" + handler + "} in this expression {" + expression + "} this is description -> " + description, NL_LOGPATH);
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
        break;
    case Network:
    case MessageBox:
        return false;
    }
    return true;
}


void NException::ForceExit()
{
    exit(-99);
}
