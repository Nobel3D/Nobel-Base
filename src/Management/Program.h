#pragma once

#include <Data/NString.h>
#include <Data/Array.h>
#include <Data/Time.h>

NL_NAMESTART

    class Program
    {
    private:
        static NString gen_sProgram;
        static NString gen_sVersion;
        static Array<NString>* gen_aArg;

    public:
        Program(const NString& _name, const NString& _version, int _argc, char** _argv);
        static NString getName();
        static NString getVersion();
        static NString getArgument(int _number);
    };

    class unixrusage;

    enum Who {useSelf = 0, useThread = 1, useChildren = -1};
    class ResourceUsage
    {
    public:
        // constructors
        ResourceUsage(Who _who);

        // time accessors
        Time utime() const;
        Time stime() const;

        // accessors
        llint maxrss() const;
        llint ixrss() const;
        llint idrss() const;
        llint isrss() const;
        llint minflt() const;
        llint majflt() const;
        llint nswap() const;
        llint inblock() const;
        llint oublock() const;
        llint msgsnd() const;
        llint msgrcv() const;
        llint nsignals() const;
        llint nvcsw() const;
        llint nivcsw() const;

        void Update();
    private:
        int who;

        unixrusage* usage;
};

NL_NAMECLOSE
