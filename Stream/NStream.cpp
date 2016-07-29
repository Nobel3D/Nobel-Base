
NL_NAMEUSING
using namespace NobelLib::IO;

NStream::NStream()
{
}

NStream::~NStream()
{
	Close();
}

int NStream::Close()
{
	return 1;
}

bool NStream::CanLoad()
{
	return false;
}

bool NStream::Open(OpenMode Mode)
{
	return CanLoad();
}

int NStream::Write()
{
	return 1;
}
void NStream::WriteLine(const char* Send)
{
	NString strSend = NString(Send) + "\n";
	createBuffer(strSend);
	Write();
}

void NStream::WriteStr(const char* Send)
{
	createBuffer(Send);
	Write();
}

void NStream::WriteBin(Array<BYTE>* Send)
{
	createBuffer(Send);
	Write();
}

void NStream::createBuffer(BYTE* sendBuffer)
{
	stmSize = sendBuffer->SizeArray();
	stmBuffer = sendBuffer;
}
void NStream::createBuffer(const char* sendBuffer)
{
	stmSize = strlen(sendBuffer);
	this->stmBufferASCII = new char[stmSize];

	for (int i = 0; i<stmSize; i++)
	{
		stmBufferASCII[i] = sendBuffer[i];
	}
}

NStream& NStream::operator<< (const char* str)
{
	WriteLine(str);
	return *this;
}
NStream& NStream::operator<<(Array<BYTE>& str)
{
	createBuffer(&str);
	return *this;
}
NStream& NStream::operator>>(Array<BYTE>& str)
{
	createBuffer(&str);
	return *this;
}
NStream& NStream::operator<<(NStream & str)
{
	Writing(str.Reading(stmSize));
	return *this;
}
NStream& NStream::operator>>(NStream & str)
{
	str.Writing(Reading(stmSize));
	return *this;
}
bool NStream::isEoF()
{
	return stm_bEoF;
}
Array<BYTE>* NStream::Reading(LLINT sizePackage)
{
	Array<BYTE>* Package = new Array<BYTE>(sizePackage);
	BYTE buffer = ' ';
	int i = 0;
	while(i < sizePackage && !stm_bEoF)
	{
		if (Read(&buffer, sizeof(BYTE)))
		{
			(*Package)[i] = buffer;
			i++;
		}
	}

	return Package;
}
int NStream::Writing(Array<BYTE>* Send)
{
	createBuffer(Send);
	return Write();
}
NString NStream::ReadLine()
{
	NString strRet = "";
	char c='!';
	do
	{
		if (Read(&c, sizeof(char)))
			strRet += c;
	}
	while (c != '\n' && !stm_bEoF);

	return strRet;
}
Array<BYTE>* NStream::ReadAll(void)
{
	List<BYTE> ret;
	BYTE buffer = ' ';
	do
	{
		if (Read(&buffer, sizeof(BYTE)))
			ret.addItem(buffer);
		else
			break;
	} while (true);

	return ret.toArray();
}
