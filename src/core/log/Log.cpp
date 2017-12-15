#include "core/log/Log.hpp"

class PrintfLogHandler : public LogHandler
{
	virtual void log(CStr message) override
	{
		printf(message.c_str());
	}
} gPrintfLogHandler;

LogHandler::LogHandler()
{
	LogSystem::get().addHandler(*this);
}

LogHandler::~LogHandler()
{
	LogSystem::get().removeHandler(*this);
}

void LogSystem::log(CStr msg)
{
	printf("log!\n");
	for(auto&& handler: mHandlers)
	{
		printf("loggy\n");
		handler.log(msg);
	}

	printf("done\n");
}

void LogSystem::addHandler(LogHandler& logHandler)
{
	mHandlers.insertTail(logHandler);
}

void LogSystem::removeHandler(LogHandler& logHandler)
{
	mHandlers.remove(logHandler);
}