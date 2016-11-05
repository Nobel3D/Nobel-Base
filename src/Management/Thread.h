#pragma once

#include <def.h>

NL_NAMESTART

    typedef unsigned long int unixthread;
    union unixattr;

    class Thread
    {
    private:
        unixthread th_ID;
        bool th_bStart;
    public:
        Thread();
        bool Start(const unixattr *_attr, void* (*_main)(void*), void* _arg);
        bool Start(void* (*_main)(void*));
        static void Close(void* exitcode);
        void Close();

        static unixthread getID();
    };

NL_NAMECLOSE
