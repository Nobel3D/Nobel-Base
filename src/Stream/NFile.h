#pragma once

#include <def.h>
#include <Data/NString.h>
#include <Management/NException.h>
#include "NStream.h"
#include "Filename.h"

NL_NAMESTART

		class NFile : public NStream
		{
		private:
            Filename* file;
            OpenMode mode;
			bool bStart = false;

			bool CanLoad();
            NString getModeOpen(OpenMode _mode);
		public:
            NFile(const Filename& _file);
			~NFile();
            void Destroy();

            bool Open(OpenMode _mode);
			int Close();

			bool IsStarted();
			INDEX getLenght();

            INDEX Read();
            INDEX Write();

            Filename& getName() const;
		};

NL_NAMECLOSE
