#include "NException.h"

NL_NAMEUSING

NException::NException(NString handler, NString expression, NString description, NString info, void* badpointer)
{
    ex_sHandler = handler;
    ex_sExpression = expression;
    ex_sDescription = description;
    ex_sInfo = info;
    ex_vPointer = badpointer;
}

NException::NException(NString handler, NString expression, NString description, NString info)
{
    ex_sHandler = handler;
    ex_sExpression = expression;
    ex_sDescription = description;
    ex_sInfo = info;
}

NException::~NException()
{
    //dtor
}
