#include "NFile.h"
#include <stdio.h>

NL_NAMEUSING

NFile::NFile(const NString& path) : NStream::NStream(path)
{
}

NFile::~NFile()
{
}

bool NFile::Open(OpenMode OMode, bool isBinary)
{
    res_bBinary = isBinary;
    ASSERT(!txt_bStart)

    stm_using = fopen(stm_sPath, getModeOpen(OMode));
    Mode = OMode;
    txt_bStart = true;
    return true;
}

bool NFile::CanLoad()
{
	if (FILE *file = fopen(stm_sPath, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

bool NFile::IsStarted()
{
	return txt_bStart;
}

INDEX NFile::getLenght()
{
	return ftell((FILE*)stm_using);
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
	if (txt_bStart)
		return fclose((FILE*)stm_using);
}

int NFile::Write()
{
	return fwrite(stm_sData, 1, stm_sData.getLength(), (FILE*)stm_using);
}

INDEX NFile::Read(void* vpGet, INDEX length, INDEX count)
{

    ASSERT (Mode == OpenMode::Reading)
    INDEX result = 0;

    result = fread(vpGet, count, length, (FILE*)stm_using);
    if (result == length)
        return length;
    else
		stm_bEoF = true;

    return 0;
}

void NFile::Write(byte* bin)
{
		fwrite(bin, sizeof(bin), 1, (FILE*)stm_using);
}

NString NFile::getName() const
{
    return stm_sPath;
}
