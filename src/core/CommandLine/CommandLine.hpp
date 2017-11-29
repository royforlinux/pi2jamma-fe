#pragma once

#include "core/CommandLine/CommandLineHandler.hpp"

class CommandLine
{
public:
	static CommandLine& get();
	void addHandler(const CommandLineHandler& handler);
	void removeHandler(const CommandLineHandler& handler);

	Result parse(int argc, const char* argv[]);
	void printHelp() const;

private:

	CStr mApplicationPath;

	RbTree<
		CommandLineHandler,
		CStr,
		KeyFinderGetter<
			CommandLineHandler,
			CStr,
			& CommandLineHandler::getShortName>,
		NodeFinder<
			CommandLineHandler,
			& CommandLineHandler::mShortNameNode>> mHandlersByShortName;

	RbTree<
		CommandLineHandler,
		CStr,
		KeyFinderGetter<
			CommandLineHandler,
			CStr,
			& CommandLineHandler::getLongName>,
		NodeFinder<
			CommandLineHandler,
			& CommandLineHandler::mLongNameNode>> mHandlersByLongName;
};

