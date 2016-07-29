#pragma once
#include <def.h>
#include <Data/NString.h>
#include <NException.h>
#include "NStream.h"
#include <stdio.h>

NL_NAMESTART
	namespace IO
	{

		class NFile : public NStream
		{
		private:
			NString txt_sPath;
			FILE* LinkFile;
			OpenMode Mode;
			bool Start;
			bool res_bBinary;

			bool CanLoad();
			NString getModeOpen(OpenMode _Mode);

		public:
			NFile(NString path);
			~NFile();
			bool Open(OpenMode OMode,bool isBinary = false);
			int Close();

			bool IsStarted();
			llint getLenght();

			int Write();
			llint Read(void* vpGet, llint length, llint count = 1);
			void Write(byte* bin);
		};
	}
NL_NAMECLOSE
