#include "Filename.h"

NL_NAMEUSING

Filename::Filename(const char* filename)
{
    sFile =  new NString(filename);
}
Filename::Filename(const NString& filename)
{
    sFile = new NString(filename);
}

Filename::Filename(const Filename& filename)
{
    sFile = new NString(*filename.sFile);
}

NString& Filename::getPath() const
{
    NString* strOutput = new NString;
    int length = sFile->getLength();
    for (int i = length; i > 0; i--)
        if((*sFile)[i] == NL_CHAR_PATH)
        {
            length = i + 1;
            break;
        }

    if(length != sFile->getLength())
        *strOutput = sFile->Cut(length);

    return *strOutput;
}

NString& Filename::getName() const
{
    NString* strOutput = new NString(*this->sFile); //File can't have no Name

    int length = sFile->getLength();
    for (int i = length; i > 0; i--)
        if((*sFile)[i] == NL_CHAR_PATH)
        {
            length = i + 1;
            break;
        }

    if(length != sFile->getLength())
        *strOutput = sFile->Sub(length);

    return *strOutput;
}

NString& Filename::getExt() const
{
    NString* strOutput = new NString;

    int length = sFile->getLength();
    for (int i = length; i > 0; i--)
        if((*sFile)[i] == '.')
        {
            length = i;
            break;
        }

    if(length != sFile->getLength())
        *strOutput = sFile->Sub(length);

    return *strOutput;
}

NString& Filename::getAll() const
{
    NString* strOutput = new NString(*this->sFile);

    return *strOutput;
}

void Filename::operator =(const Filename& file)
{
    if(sFile != nullptr)
        sFile->Delete();
    sFile = new NString(*file.sFile);
}

bool Filename::operator==(const Filename& file)
{
    return *this->sFile == *file.sFile;
}

bool Filename::operator!=(const Filename& file)
{
    return *this->sFile != *file.sFile;
}

