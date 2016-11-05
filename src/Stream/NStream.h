#pragma once

#include <def.h>
#include <Data/NString.h>


NL_NAMESTART

		enum OpenMode { Writing = 8, Reading = 16, Append = 32 };
		enum TypeStream { LocalFile=8, NetworkConnection=16, DataBase=32, Crypter=64 };

		class NStream
		{
		public:
			NStream(const NString& path);

			virtual int Close();

			void WriteLine(const NString& send);
			void Write(const NString& send);

			virtual int Write() = 0;
			virtual INDEX Read(void* vpGet, INDEX length, INDEX count = 1) = 0;

			NString ReadLine();
			NString ReadAll();

			NStream& operator <<(const char* str);
			NStream& operator <<(const NString& str);
			NStream& operator >>(NString& str);

			bool isEoF();
		protected:
		    NString stm_sPath;
			NString stm_sData;

			STREAM stm_using;

			bool stm_bEoF = false;
		};
NL_NAMECLOSE
