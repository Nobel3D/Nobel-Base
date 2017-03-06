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

bool NFile::Open(OpenMode _mode)
{

    if(bStart)
    {
        NL_LOG("FILE", file->getAll() + " is already opened. Ignoring")
        return false;
    }

    pStream = fopen(file->getAll(), getModeOpen(_mode));

    if(pStream == 0)
    {
        NL_LOG("FILE", file->getAll() + " cannot be open")
        return false;
    }

    mode = _mode;
    bStart = true;
    return true;
}

bool NFile::CanLoad()
{
        if (FILE* _file = fopen(file->getAll(), "r")) {
                fclose(_file);
		return true;
	}
	else {
		return false;
	}
}

bool NFile::IsStarted()
{
	return bStart;
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
	if (bStart)
		return fclose((FILE*)pStream);
    else
        return -1;
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
