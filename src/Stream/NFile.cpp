#include "NFile.h"
#include <stdio.h>

NL_NAMEUSING

NFile::NFile(const Filename& _file)
{
    file = new Filename(_file);
}

NFile::~NFile()
{
    delete[] file;
}

int NFile::Open(OpenMode _mode, bool binary)
{
    bBinary = binary;
    pStream = fopen(file->getAll(), getModeOpen(_mode));

    if(pStream == nullptr)
    {
        NL_LOG("FILE", file->getAll() + " cannot be open");
        return false;
    }

    mode = _mode;
    return NL_OK;
}

int NFile::CanLoad()
{
    void* _file = fopen(file->getAll(), "r");
    fclose((FILE*)_file);

    return _file != nullptr ? NL_OK : NL_FAIL;
}

bool NFile::IsStarted()
{
    return pStream != nullptr;
}

INDEX NFile::getLenght()
{
    return ftell((FILE*)pStream);
}

NString NFile::getModeOpen(OpenMode _mode)
{
        NString type = NString();
        if (_mode == OpenMode::Reading)
	{
                type += "r";
	}
        if (_mode == OpenMode::Writing)
	{
                type += "w";
	}
        if (_mode == OpenMode::Append)
	{
                type += "a";
	}
        return type;
}

int NFile::Close()
{
    return fclose((FILE*)pStream);
}

INDEX NFile::Write()
{
    ASSERT (mode == OpenMode::Writing);
    return fwrite(pData, 1, iSize, (FILE*)pStream);
}

INDEX NFile::Read()
{
    ASSERT (mode == OpenMode::Reading);

    pData = new byte[iSize];

    if (fread(pData, 1, iSize, (FILE*)pStream) == iSize)
        return iSize;
    else
        bEoS = true;

    return 0;
}

Filename& NFile::getName() const
{
    Filename* out = new Filename(*file);
    return *out;
}
