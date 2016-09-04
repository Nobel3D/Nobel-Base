#include "Log.h"
#include <Stream/NFile.h>

NL_NAMEUSING

	Log::Log(const NString& path)
	{
	    txt_sLog = path;
	}

	Log::~Log()
	{
	    txt_sLog.Delete();
	}

	NString Log::Add(const NString& handler, const NString& text)
	{
        NString strLog = "[" + handler + "] " + Time::Print(Time::Now()) + " -> " + text;
        NFile fileLog(txt_sLog);
        fileLog.Open(Append);
		fileLog.WriteLine(strLog);
		fileLog.Close();
		return strLog;
	}

	NString Log::Add(const NString& handler, const NString& text, const NString& path)
	{
	    Log log(path);
	    return log.Add(handler, text);
	}
