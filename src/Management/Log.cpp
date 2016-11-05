#include "Log.h"
#include <Stream/NFile.h>
#include <stdio.h>

NL_NAMEUSING

	Log::Log(const NString& path)
	{
	    txt_sLog = path;
	}

	Log::~Log()
	{
	    txt_sLog.Delete();
	}

	void Log::Add(const NString& handler, const NString& text)
	{
        NString strLog = "[" + handler + "] " + Time::Print(Time::Now()) + ":" + text + '\n';
        FILE* fileLog = fopen(txt_sLog,"a");
        fwrite(strLog, strLog.getLength(), 1, fileLog);
        fclose(fileLog);
	}

	void Log::Add(const NString& handler, const NString& text, const NString& path)
	{
	    Log log(path);
	    log.Add(handler, text);
    }
