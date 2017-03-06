#pragma once

#include <def.h>
#include <Data/NString.h>


NL_NAMESTART

		enum OpenMode { Writing = 8, Reading = 16, Append = 32 };
		enum TypeStream { LocalFile=8, NetworkConnection=16, DataBase=32, Crypter=64 };

		class NStream
		{
		protected:
            STREAM pStream = nullptr;
            SIZE iSize = 1;
            byte* pData = nullptr;
            bool bEoS = false;
		public:
			NStream();

			virtual int Close() = 0;

			void WriteLine(const NString& send);

            virtual INDEX Write() = 0;
            virtual INDEX Read() = 0;

			NString ReadLine();
			NString ReadAll();

            int decode_int();
            char decode_ascii();

            int encode_int(const int value);
            int encode_ascii(const char* value);

			NStream& operator <<(const char* str);
			NStream& operator <<(const NString& str);
			NStream& operator >>(NString& str);
            NStream& operator >>(int& value);

            bool isEoS();
		};
NL_NAMECLOSE
