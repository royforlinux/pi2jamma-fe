#pragma once

#include "core/container/DlList.hpp"
#include "core/CString.hpp"
#include "core/StringUtil.hpp"

class LogHandler
{
public:

	virtual ~LogHandler();
	virtual void log(CStr cStr) = 0;

protected:

	LogHandler();

	DlListNode mListNode;

friend class LogSystem;
};

class LogSystem
{
public:
	static LogSystem& get();

	void log(CStr msg);

private:	
	void addHandler(LogHandler& logHandler);
	void removeHandler(LogHandler& logHandler);

	DlList<
		LogHandler,
		NodeFinderField<
			LogHandler,
			DlListNode,
			& LogHandler::mListNode>> mHandlers;

	friend class LogHandler;
};

inline LogSystem& LogSystem::get()
{
	static LogSystem sLogSystem;
	return sLogSystem;
}


inline void Log(CStr message)
{
	LogSystem::get().log(message);
}

#define LogFmt(fmt, ...) \
{ \
	LogSystem::get().log(formatString(fmt, __VA_ARGS__)); \
}
