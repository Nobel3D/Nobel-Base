#include "NFile.h"
#include <stdio.h>

NL_NAMEUSING

NFile::NFile(const NString& path)
{
    sFile = path;
}

NFile::~NFile()
{
}

bool NFile::Open(OpenMode OMode, bool isBinary)
{
    bBinary = isBinary;

    if(!bStart)
    {
        pStream = fopen(sFile, getModeOpen(OMode));
        Mode = OMode;
        bStart = true;
        return true;
    }

    return false;
}

bool NFile::CanLoad()
{
	if (FILE *file = fopen(sFile, "r")) {
		fclose(file);
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

NString NFile::getModeOpen(OpenMode _Mode)
{
	NString TypeOpen = NString();
	if (_Mode == OpenMode::Reading)
	{
		TypeOpen += "r";
	}
	if (_Mode == OpenMode::Writing)
	{
		TypeOpen += "w";
	}
	if (_Mode == OpenMode::Append)
	{
		TypeOpen += "a";
	}
	return TypeOpen;
}

int NFile::Close()
{
	if (bStart)
		return fclose((FILE*)pStream);
}

int NFile::Write(NString _string)
{
	return fwrite(_string, 1, _string.getLength(), (FILE*)pStream);
}

INDEX NFile::Read(void* vpGet, INDEX length, INDEX count)
{

    ASSERT (Mode == OpenMode::Reading)
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
    fwrite(bin, length, 1, (FILE*)pStream);
}

NString NFile::getName() const
{
    return sFile;
}
