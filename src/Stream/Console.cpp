#include "Console.h"
#include <stdio.h>

NL_NAMEUSING

Console::Console()
{
}

INDEX Console::Read(void* vpGet, INDEX length, INDEX count)
{
    return fread(vpGet, length, count, stdin);
}

int Console::Write(NString _string)
{
    return fwrite(_string, _string.getLength(),1, stdout);
}

int Console::Write(byte* bin, INDEX length)
{
    return fwrite(bin, length, 1, stdout);
}
