#pragma once

#include <def.h>
#include <Data/NString.h>


namespace NobelLib
{
	namespace IO
	{
		enum OpenMode { Writing = 8, Reading = 16, Append = 32 };
		enum TypeStream { LocalFile=8, NetworkConnection=16, DataBase=32, Crypter=64 };

		class NStream
		{
		protected:
			byte* stmBuffer;
			char* stmBufferASCII;
			llint stmSize = 1024;

			uint stmUsed;
			bool stm_bEoF = false;
			void createBuffer(const char* sendBuffer);
			void createBuffer(byte* sendBuffer);
			virtual bool CanLoad();
		public:
			NStream();
			~NStream();

			virtual bool Open(OpenMode OpenFile);
			virtual int Close();

			void WriteLine(const char* Send);
			void WriteStr(const char* Send);
			void WriteBin(byte* Send);

			virtual int Write() = 0;
			virtual llint Read(void* vpGet, llint length, llint count = 1) = 0;

			byte* Reading(llint sizePackage);
			int Writing(Array<byte>* Send);
			NString ReadLine();
			byte* ReadAll();

			NStream& operator <<(const char* str);
			NStream& operator >>(NString &str) { str = ReadLine(); return *this; }
			NStream& operator <<(Array<byte>& str);
			NStream& operator >>(Array<byte> &str);
			NStream& operator <<(NStream& str);
			NStream& operator >>(NStream &str);

			void setPackageSize(llint newSize) { stmSize = newSize; }
			llint getPackageSize() { return stmSize; }

			bool isEoF();
		};
	}
}
