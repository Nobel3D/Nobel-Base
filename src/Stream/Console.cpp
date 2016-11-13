#include "Console.h"
#include <stdio.h>

NL_NAMEUSING

Console::Console()
{

}

INDEX Console::Read(void* vpGet, INDEX length, INDEX count)
{
    fread(vpGet, length, count, stdin);
}

int Console::Write()
{
    fwrite(stm_sData,stm_sData.getLength(),1, stdout);
}
