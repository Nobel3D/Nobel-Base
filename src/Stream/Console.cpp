#include "Console.h"
#include <stdio.h>

NL_NAMEUSING

Console::Console()
{
    bBinary = true;
}

INDEX Console::Write()
{
    return fwrite(pData, 1, iSize, (FILE*)pStream);
}

INDEX Console::Read()
{
    return fread(pData, 1, iSize, (FILE*)pStream);
}
