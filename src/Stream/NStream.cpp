#include "NStream.h"
#include <stdio.h>

NL_NAMEUSING

NStream::NStream()
{
}

void NStream::WriteLine(const NString& send)
{
	Write(send + '\n');
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
	return bEoF;
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
	while (buffer != '\n' && !bEoF);
	Memory* stack = data.toStack();
	stack->Cut(data.getLength() + 1);
	NString* strOffset = new NString(*stack);

	return *strOffset;
}
NString NStream::ReadAll()
{
    List<byte> data;
	byte buffer = ' ';
	do
	{
		if (Read(&buffer, 1))
			data.addItem(buffer);
	}
	while (!bEoF);

        return NString((byte*)data.toStack()->getPointer());
}
