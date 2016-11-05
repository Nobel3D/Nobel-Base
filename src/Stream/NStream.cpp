#include "NStream.h"
#include <stdio.h>

NL_NAMEUSING

NStream::NStream(const NString& path)
{
    stm_sPath = path;
}

int NStream::Close()
{
    stm_sPath.Delete();

}

int NStream::Write()
{
	return 1;
}
void NStream::WriteLine(const NString& send)
{
    stm_sData = send + '\n';
	Write();
}

void NStream::Write(const NString& send)
{
    stm_sData = send;
	Write();
}

NStream& NStream::operator<< (const char* str)
{
	WriteLine(str);
	return *this;
}
NStream& NStream::operator<<(const NString& str)
{
	Write(str);
	return *this;
}
NStream& NStream::operator >>(NString& str)
{
    str = ReadLine();
    return *this;
}
bool NStream::isEoF()
{
	return stm_bEoF;
}

NString NStream::ReadLine()
{
	List<byte> data;
	byte buffer = ' ';

	do
	{
		if (Read(&buffer, 1))
			data.addItem(buffer);
	}
	while (buffer != '\n' && !stm_bEoF);
    data.list_lManager.Cut();
	NString* strOffset = new NString(*data.list_lManager.toStack());

	return *strOffset;
}
NString NStream::ReadAll()
{
	INDEX _size;
    fseek ((FILE*)stm_using , 0 , SEEK_END);
    _size = ftell ((FILE*)stm_using);
    rewind ((FILE*)stm_using);

    byte* buffer = new byte[_size];

    Read(buffer,_size);

	return NString(buffer);
}
