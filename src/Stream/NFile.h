#pragma once

#include <def.h>
#include <Data/NString.h>
#include <Management/NException.h>
#include "NStream.h"
#include <stdio.h>

NL_NAMESTART

		class NFile : public NStream
		{
		private:
			FILE* LinkFile;
			OpenMode Mode;
			bool txt_bStart = false;
			bool res_bBinary;

			bool CanLoad();
			NString getModeOpen(OpenMode _Mode);

		public:
			NFile(const NString& path);
			~NFile();
			bool Open(OpenMode OMode,bool isBinary = false);
			int Close();

			bool IsStarted();
			index getLenght();

			int Write();
			index Read(void* vpGet, index length, index count = 1);
			void Write(byte* bin);
		};

NL_NAMECLOSE
