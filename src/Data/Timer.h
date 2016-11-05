#pragma once

#include <def.h>
#include <Management/Thread.h>

NL_NAMESTART

    class Timer
    {
    private:
        static llint time_usec;
        llint time_delta;
        Thread* time_cThread;
        static llint time_unity;

        static void* timer(void* null);
    public:
        Timer();
        void Start(llint _unity);
        void Quit();
        void Reset();
        llint getTime();
    };

NL_NAMECLOSE
