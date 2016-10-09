#include "Program.h"
#include <sys/time.h>
#include <sys/resource.h>

NL_NAMESTART


    NString Program::gen_sProgram;
    NString Program::gen_sVersion;
    Array<NString>* Program::gen_aArg;
    char** Program::gen_pArg;
    int Program::gen_iArg;
    Program::Program(const NString& _name,const NString& _version, int _argc, char** _argv)
    {
        gen_sProgram = _name;
        gen_sVersion = _version;
        gen_aArg = new Array<NString>(_argc);
        gen_pArg = _argv;
        gen_iArg = _argc;
        for(int i=0; i< gen_iArg; i++)
            (*gen_aArg)[i] = NString(gen_pArg[i]);
    }

    NString Program::getName() { return gen_sProgram; }
    NString Program::getVersion() { return gen_sVersion; }
    NString Program::getArgument(int _number) { ASSERT(gen_aArg->getSize() > _number); return (*gen_aArg)[_number]; }
    char** Program::getArgument() { return gen_pArg; }
    int* Program::getNumberArg() { return &gen_iArg; }

    class unixrusage : public rusage {

     };


    ResourceUsage::ResourceUsage(Who _who)
    {
        usage = new unixrusage;
        who = _who;
        Update();
    }

    void ResourceUsage::Update()
    {
        ASSERT(getrusage(who, (rusage*)usage) == 0);
    }

    Time ResourceUsage::utime() const { return Time(usage->ru_utime.tv_sec); }
    Time ResourceUsage::stime() const { return Time(usage->ru_stime.tv_sec); }

    llint ResourceUsage::maxrss() const { return usage->ru_maxrss; }
    llint ResourceUsage::ixrss() const { return usage->ru_ixrss; }
    llint ResourceUsage::idrss() const { return usage->ru_idrss; }
    llint ResourceUsage::minflt() const { return usage->ru_minflt; }
    llint ResourceUsage::majflt() const { return usage->ru_majflt; }
    llint ResourceUsage::nswap() const { return usage->ru_nswap; }
    llint ResourceUsage::inblock() const { return usage->ru_inblock; }
    llint ResourceUsage::oublock() const { return usage->ru_oublock; }
    llint ResourceUsage::msgsnd() const { return usage->ru_msgsnd; }
    llint ResourceUsage::msgrcv() const { return usage->ru_msgrcv; }
    llint ResourceUsage::nsignals() const { return usage->ru_nsignals; }
    llint ResourceUsage::nvcsw() const { return usage->ru_nvcsw; }
    llint ResourceUsage::nivcsw() const { return usage->ru_nivcsw; }

NL_NAMECLOSE
