#pragma once

#include "core/container/RbTree.hpp"
#include "core/CString.hpp"
#include "core/Property.hpp"
#include "core/Result.hpp"

class CommandLineHandler
{
public:
	CommandLineHandler(CStr shortName, CStr longName);
	~CommandLineHandler();

	virtual Result parse(const char**& ppToken, const char** ppEnd) = 0;
	virtual CStr getHelp() const = 0;

	PROPERTY(CStr, ShortName);
	PROPERTY(CStr, LongName);

public:

	RbTreeNode<CommandLineHandler*> mShortNameNode;
	RbTreeNode<CommandLineHandler*> mLongNameNode;
};

class CommandLine
{
public:
	static CommandLine& get();
	void addHandler(CommandLineHandler* pHandler);
	void removeHandler(CommandLineHandler* pHandler);

	Result parse(int argc, const char* argv[]);
	void printHelp() const;

private:
	static CStr getShortName(const CommandLineHandler* pH);
	static CStr getLongName(const CommandLineHandler* pH);

	CStr mApplicationPath;

	RbTree<CommandLineHandler*, CStr, getShortName> mHandlersByShortName;
	RbTree<CommandLineHandler*, CStr, getLongName> mHandlersByLongName;
};

