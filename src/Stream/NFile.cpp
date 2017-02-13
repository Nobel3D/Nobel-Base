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

bool NFile::Open(OpenMode _mode, bool isBinary)
{
    bBinary = isBinary;

    if(!bStart)
    {
        pStream = fopen(file->getAll(), getModeOpen(_mode));
        mode = _mode;
        bStart = true;
        return true;
    }

    return false;
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

int NFile::Write(NString _string)
{
	return fwrite(_string, 1, _string.getLength(), (FILE*)pStream);
}

INDEX NFile::Read(void* vpGet, INDEX length, INDEX count)
{

    ASSERT (mode == OpenMode::Reading)
    INDEX result = 0;

    result = fread(vpGet, count, length, (FILE*)pStream);
    if (result == length)
        return length;
    else
		bEoF = true;

    return 0;
}

int NFile::Write(byte* bin, INDEX length)
{
    return fwrite(bin, length, 1, (FILE*)pStream);
}

Filename& NFile::getName() const
{
    Filename* out = new Filename(*file);
    return *out;
}
