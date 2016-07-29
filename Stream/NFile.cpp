#include "NFile.h"


NL_NAMEUSING
using namespace NobelLib::IO;

NFile::NFile(NString Path)
{
	txt_sPath = Path;
}

NFile::~NFile()
{
    txt_sPath.Delete();
}

bool NFile::Open(OpenMode OMode, bool isBinary)
{
    try
    {
        res_bBinary = isBinary;
        if(IsStarted())
            throw NException("bool NFile::Open(OpenMode OMode, bool isBinary)", "if(IsStarted())", "File is already started.",
                             "where OMode = " + getModeOpen(OMode) + "; isBinary = " + NString::fromBool(isBinary));
        else if (!CanLoad())
            throw NException("bool NFile::Open(OpenMode OMode, bool isBinary)", "else if (!CanLoad())", "File isn't loadble.",
                            "where this->txt_sPath = " + txt_sPath + "; OMode = " + getModeOpen(OMode) + "; isBinary = " + NString::fromBool(isBinary));
        else
        {
            LinkFile = fopen(txt_sPath, getModeOpen(OMode));
            Mode = OMode;
            Start = true;
            return true;
        }
    }
    catch(NException ex)
    {

    }
}
bool NFile::CanLoad()
{
	if (FILE *file = fopen(txt_sPath, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
bool NFile::IsStarted()
{
	return Start;
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
	if (IsStarted())
		return fclose(LinkFile);
}

int NFile::Write()
{
	return fwrite(stmBuffer, 1, stmSize, LinkFile);
}

llint NFile::Read(void* vpGet, llint length, llint count)
{
    try
    {
        if (Mode != OpenMode::Reading)
            throw NException("llint NFile::Read(void* vpGet, llint length, llint count)", "if (Mode != OpenMode::Reading)","You are tring to read in a writing.",
                             "where vpGet = ");

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
    }
    //TODO catch
	{
		vpGet = NULL;
	}
}



void NFile::Write(BYTE* bin)
{
	if (res_bBinary)
	{
		fwrite(bin, sizeof(bin), 1, LinkFile);
	}
	else
	{
		Error("NobelLib::IO::NFile::Write(BinaryFile) Impossible use binary stream in text stream!", 20, false);
	}
}
