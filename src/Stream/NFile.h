#pragma once

#include <def.h>
#include <Data/NString.h>
#include <Management/NException.h>
#include "NStream.h"

NL_NAMESTART

		class NFile : public NStream
		{
		private:
		    NString sFile;
			OpenMode Mode;
			bool bStart = false;

			bool CanLoad();
			NString getModeOpen(OpenMode _Mode);
		public:
			NFile(const NString& path);
			~NFile();
			bool Open(OpenMode OMode,bool isBinary = false);
			int Close();

			bool IsStarted();
			INDEX getLenght();

			INDEX Read(void* vpGet, INDEX length, INDEX count = 1);

			int Write(NString _string);
			int Write(byte* bin, INDEX length);

			NString getName() const;
		};

NL_NAMECLOSE
