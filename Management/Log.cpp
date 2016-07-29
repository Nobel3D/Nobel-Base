#include "Log.h"

NL_NAMEUSING

	Log::Log(NString path)
	{
	    if(path.Null())
            txt_fLog = new NFile(NL_LOGPATH);
		else
            txt_fLog = new NFile(path);
	}

	Log::~Log()
	{
	    txt_fLog->~NFile();
	}

	void Log::Add(NString handler, NString text)
	{
        txt_fLog->Open(Append);
		txt_fLog->WriteLine(NString("[") + handler + "] " + Time::NowTime() + " -> " + text);
		txt_fLog->Close();
	}

	void Log::Add(NString handler, NString text, NString path)
	{
	    Log* log = new Log(path);
	    log->Add(handler, path);
	    log->~Log();
	}
