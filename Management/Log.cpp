#include "Log.h"
#include <Stream/NFile.h>

NL_NAMEUSING

	Log::Log(NString path)
	{
	    txt_sLog = path;
	}

	Log::~Log()
	{
	    txt_sLog.Delete();
	}

	NString Log::Add(NString handler, NString text)
	{
	    NString strLog = "[" + handler + "] " + Time::NowTime() + " -> " + text;
        NFile fileLog(txt_sLog);
        fileLog.Open(Append);
		fileLog.WriteLine(strLog);
		fileLog.Close();
	}

	NString Log::Add(NString handler, NString text, NString path)
	{
	    Log log(path);
	    log.Add(handler, path);
	    log.~Log();
	}
