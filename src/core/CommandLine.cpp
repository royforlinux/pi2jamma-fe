#include "core/CommandLine.hpp"

#include "core/cast.hpp"
#include "core/StringUtil.hpp"
#include "core/file/FilePath.hpp"

class CommandLineHandlerHelp : public CommandLineHandler
{
public:
	CommandLineHandlerHelp()
		: CommandLineHandler("--help", "-h")
	{}

	virtual Result parse(const char**& pS, const char** pEnd)
	{
		CommandLine::get().printHelp();
		return Result::makeSuccess();
	}

	CStr getHelp() const {
		return "Print help.";
	}
};

static CommandLineHandlerHelp gHelp;

CommandLineHandler::CommandLineHandler(CStr shortName, CStr longName)
	: mShortName(shortName)
	, mLongName(longName)
	, mShortNameNode(this)
	, mLongNameNode(this)
{
	CommandLine::get().addHandler(this);	
}

CommandLineHandler::~CommandLineHandler()
{
	CommandLine::get().removeHandler(this);
}

CommandLine& CommandLine::get()
{
	static CommandLine sCommandLine;
	return sCommandLine;
}

Result CommandLine::parse(int argc, const char* argv[])
{
	mApplicationPath = argv[0];

	const char** ppStart = & argv[1];
	const char** ppEnd = & argv[argc];	

	const char** ppCurrent = ppStart;

	while(ppCurrent < ppEnd) {
		Log("Testy\n");
		CommandLineHandler* pH = safeDeRef(mHandlersByShortName.findItem(*ppCurrent));
		if(nullptr == pH) {
			pH = safeDeRef(mHandlersByLongName.findItem(*ppCurrent));
	
			if(nullptr == pH) {
				printHelp();
				return Result::makeFailureWithString(formatString("unrecognized argument: '%s'", *ppCurrent ));
			}
		}

		ppCurrent++;

		Result r = pH->parse(ppCurrent, ppEnd);
		if (r.peekFailed()) {
			printHelp();
			return r;
		}
	}

	return Result::makeSuccess();
}

void CommandLine::printHelp() const
{
	fprintf(
		stderr,
		"%s Help:\n",
		getPathEntryName(mApplicationPath).c_str());

	for(auto&& h : mHandlersByLongName)
	{
		fprintf(
			stderr,
			"\t%s, %s - %s\n",
			h->getLongName().c_str(),
			h->getShortName().c_str(),
			h->getHelp().c_str());
	}
}

void CommandLine::addHandler(CommandLineHandler* pHandler)
{
	mHandlersByShortName.insert(pHandler->mShortNameNode);
	mHandlersByLongName.insert(pHandler->mLongNameNode);
}

void CommandLine::removeHandler(CommandLineHandler* pHandler)
{
	mHandlersByShortName.remove(pHandler->mShortNameNode);
	mHandlersByLongName.remove(pHandler->mLongNameNode);
}

CStr CommandLine::getShortName(const CommandLineHandler* pH)
{
	return pH->getShortName();
}

CStr CommandLine::getLongName(const CommandLineHandler* pH)
{
	return pH->getLongName();
}
