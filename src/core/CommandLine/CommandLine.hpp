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
	static CStr getShortName(const CommandLineHandler& h);
	static CStr getLongName(const CommandLineHandler& h);

	CStr mApplicationPath;

	RbTree<
		CommandLineHandler,
		CStr,
		getShortName,
		NodeFinder<
			CommandLineHandler,
			& CommandLineHandler::mShortNameNode>> mHandlersByShortName;

	RbTree<
		CommandLineHandler,
		CStr,
		getLongName,
		NodeFinder<
			CommandLineHandler,
			& CommandLineHandler::mLongNameNode>> mHandlersByLongName;
};

