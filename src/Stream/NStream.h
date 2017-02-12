#pragma once

#include <def.h>
#include <Data/NString.h>


NL_NAMESTART

		enum OpenMode { Writing = 8, Reading = 16, Append = 32 };
		enum TypeStream { LocalFile=8, NetworkConnection=16, DataBase=32, Crypter=64 };

		class NStream
		{
		protected:
			STREAM pStream;

			bool bEoF = false;
			bool bBinary = false;
		public:
			NStream();

			virtual int Close() = 0;

			void WriteLine(const NString& send);

			virtual int Write(NString _string) = 0;
			virtual int Write(byte* bin, INDEX length) = 0;
			virtual INDEX Read(void* vpGet, INDEX length, INDEX count = 1) = 0;

			NString ReadLine();
			NString ReadAll();

			NStream& operator <<(const char* str);
			NStream& operator <<(const NString& str);
			NStream& operator >>(NString& str);

			bool isEoF();
		};
NL_NAMECLOSE
