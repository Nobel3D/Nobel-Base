#pragma once

#include <Data/NString.h>

NL_NAMESTART

class Filename
{
    private:
        NString* sFile;
    public:
        Filename(const NString& filename);
        Filename(const char* filename);
        Filename(const Filename& filename);

        NString& getPath() const;
        NString& getName() const;
        NString& getExt() const;
        NString& getAll() const;

        void operator=(const Filename& file);
        bool operator==(const Filename& file);
        bool operator!=(const Filename& file);
};

NL_NAMECLOSE
