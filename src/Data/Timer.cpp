#include "Timer.h"
#include <time.h>
#include <unistd.h>

NL_NAMESTART

    llint Timer::time_usec = 0;
    llint Timer::time_unity = 1;

Timer::Timer()
{
    time_cThread = new Thread();
}

void* Timer::timer(void* null)
{
    while(true)
    {
        usleep(time_unity);
        time_usec++;
        if(time_usec == 0xfffffff)
            time_usec = 0;
    }
}
void Timer::Start(llint _unity)
{
    ASSERT(_unity > 0);
    time_unity = _unity;
    time_cThread->Start(timer);
}

void Timer::Quit()
{
    time_cThread->Close(0);
}
void Timer::Reset()
{
    time_usec = 0;
}

llint Timer::getTime()
{
    return time_usec;
}

NL_NAMECLOSE
