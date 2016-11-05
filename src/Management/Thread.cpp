#include "Thread.h"
#include <pthread.h>

NL_NAMESTART

union unixattr {
    char __size[__SIZEOF_PTHREAD_ATTR_T];
    long int __align;
};

Thread::Thread()
{

}

bool Thread::Start(const unixattr *_attr, void* (*_main)(void*), void* _arg)
{
    if(pthread_create(&th_ID, (const pthread_attr_t*)_attr, _main, _arg) != 0)
        th_bStart = false;
    else
        th_bStart = true;

    return th_bStart;
}
bool Thread::Start(void* (*_main)(void*))
{
    if(pthread_create(&th_ID, nullptr, _main, nullptr) != 0)
        th_bStart = false;
    else
        th_bStart = true;

    return th_bStart;
}
void Thread::Close(void* exitcode)
{
    pthread_exit(exitcode);
}
void Thread::Close()
{
    pthread_cancel(th_ID);
    th_bStart = false;
}

unixthread Thread::getID()
{
    return pthread_self();
}



NL_NAMECLOSE
