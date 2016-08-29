#include "NFile.h"


NL_NAMEUSING

NFile::NFile(const NString& path) : NStream::NStream(&path)
{
}

NFile::~NFile()
{
}

bool NFile::Open(OpenMode OMode, bool isBinary)
{
    try
    {
        res_bBinary = isBinary;
        if(txt_bStart)
            throw NException("bool NFile::Open(OpenMode OMode, bool isBinary)", "if(txt_bStart)", "File is already txt_bStarted.",
                             "OMode = " + getModeOpen(OMode) + "; isBinary = " + NString::fromBool(isBinary));
        if (OMode == Reading && !CanLoad())
            throw NException("bool NFile::Open(OpenMode OMode, bool isBinary)", "else if (!CanLoad())", "File isn't loadble.",
                            "this->stm_sPath = " + stm_sPath + "; OMode = " + getModeOpen(OMode) + "; isBinary = " + NString::fromBool(isBinary));
        else
        {
            LinkFile = fopen(stm_sPath, getModeOpen(OMode));
            Mode = OMode;
            txt_bStart = true;
            return true;
        }
    }
    catch(NException ex)
    {

    }
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

llint NFile::getLenght()
{
	return ftell(LinkFile);
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
	if (res_bBinary)
	{
		TypeOpen += "b";
	}
	return TypeOpen;
}

int NFile::Close()
{
	if (txt_bStart)
		return fclose(LinkFile);
}

int NFile::Write()
{
	return fwrite(stm_sData, 1, stm_sData.getLength() + 1, LinkFile);
}

llint NFile::Read(void* vpGet, llint length, llint count)
{
    try
    {
        if (Mode != OpenMode::Reading)
            throw NException("llint NFile::Read(void* vpGet, llint length, llint count)", "if (Mode != OpenMode::Reading)","You are tring to read in a writing.",
                             "vpGet = " + NString::fromAddress(vpGet) + "; length = " + NString::fromInt(length) + "; count = " + NString::fromInt(count) );

        llint result = 0;
        if (!res_bBinary)
		{
			result = fread(vpGet, count, length, LinkFile);
			if (result == length)
				return length;
			else
			{
				stm_bEoF = true;
				return 0;
			}
		}
		else
		{
			return fread(vpGet, length, count, LinkFile);
			if (result == length)
				return length;
			else
			{
				stm_bEoF = true;
				return 0;
			}
		}
	}
    catch(NException ex)
	{

	}
}

void NFile::Write(byte* bin)
{
		fwrite(bin, sizeof(bin), 1, LinkFile);
}
