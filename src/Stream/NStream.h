#pragma once

#include <def.h>
#include <Data/NString.h>
#include <Data/Memory.h>
#include <Data/Convert.h>

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
            bool bBinary = false;
		public:
			NStream();

			virtual int Close() = 0;

			void WriteLine(const NString& send);

            virtual INDEX Write() = 0;
            virtual INDEX Read() = 0;

			NString ReadLine();
			NString ReadAll();

            template<class type>
            type decode();

            int decode_int();
            float decode_float();
            double decode_double();
            char decode_ascii();

            template<class type>
            int encode(const type& value);

            int encode_int(const int &value);
            int encode_float(const float &value);
            int encode_double(const double &value);
            int encode_ascii(const char* value);

			NStream& operator <<(const char* str);
			NStream& operator <<(const NString& str);
            NStream& operator <<(const int &value);
            NStream& operator << (const float &value);
            NStream& operator << (const double &value);
			NStream& operator >>(NString& str);
            NStream& operator >>(int &value);
            NStream& operator >>(float &value);
            NStream& operator >>(double &value);

            bool isEoS();
		};

        template <class type>
        type NStream::decode()
        {
            if(bBinary)
            {
                iSize = sizeof(type);
                type* out = new type;
                Read();
                Memory::memCpy(out, pData, iSize);
                return *out;
            }
            else
            {
                NString str = ReadAll();
                if(str.Find("."))
                    return Convert::toFloat(str);
                else
                    return Convert::toInt(str);
            }
        }

        template <class type>
        int NStream::encode(const type& value)
        {
            if(bBinary)
            {
                iSize = sizeof(type);
                pData = new byte[iSize];
                Memory::memCpy(pData, &value, iSize);
                Write();
                return NL_OK;
            }
            else
            {
                pData = (byte*)Convert::toString(value);
                Write();
                return NL_OK;
            }
        }
NL_NAMECLOSE
