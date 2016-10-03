#pragma once

#include <def.h>
#include <Data/NString.h>
#include <Management/NException.h>
#include "NStream.h"
#include <stdio.h>

NL_NAMESTART

		class NFile : public NStream
		{
		public:
			NFile(const NString& path);
			~NFile();
			bool Open(OpenMode OMode,bool isBinary = false);
			int Close();

			bool IsStarted();
			INDEX getLenght();

			int Write();
			INDEX Read(void* vpGet, INDEX length, INDEX count = 1);
			void Write(byte* bin);
		private:
			FILE* LinkFile;
			OpenMode Mode;
			bool txt_bStart = false;
			bool res_bBinary;

			bool CanLoad();
			NString getModeOpen(OpenMode _Mode);
		};

NL_NAMECLOSE
