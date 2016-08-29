#pragma once

#include <def.h>
#include <Data/NString.h>


NL_NAMESTART

		enum OpenMode { Writing = 8, Reading = 16, Append = 32 };
		enum TypeStream { LocalFile=8, NetworkConnection=16, DataBase=32, Crypter=64 };

		class NStream
		{
		protected:
		    NString stm_sPath;
			NString stm_sData;

			bool stm_bEoF = false;
			virtual bool CanLoad();
		public:
			NStream(const NString& path);
            ~NStream();

			virtual bool Open(OpenMode OpenFile);
			virtual int Close();

			void WriteLine(const NString& send);
			void Write(const NString& send);

			virtual int Write() = 0;
			virtual llint Read(void* vpGet, llint length, llint count = 1) = 0;

			Array<byte>& ReadLine();
			Array<byte>& ReadAll();

			NString& Format(Array<byte>& byte2str);

			NStream& operator <<(const char* str);
			NStream& operator <<(const NString& str);
			NStream& operator >>(NString& str);

			bool isEoF();
		};
NL_NAMECLOSE
