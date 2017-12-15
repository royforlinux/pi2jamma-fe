#include "ui/elements/Console.hpp"

namespace ui {


Console::ConsoleLogHandler::ConsoleLogHandler(Console& console)
	: mConsole(console)
{
	printf("Registered!\n");
}

void Console::ConsoleLogHandler::log(CStr line)
{
	mConsole.addLine(line);
}

Console::Console(
	Element* pParent,
	const Rect& rect,
	ref<BitmapFont> refBitmapFont)
	: Element(pParent, rect)
	, mLogHandler(*this)
	, mrefBitmapFont(std::move(refBitmapFont))
{
	mLines.push_back("Hello.");
	mLines.push_back("World.");
}

void Console::clear()
{
	mLines.clear();
}

void Console::render(RenderContext& renderContext)
{
	auto fontHeight = mrefBitmapFont->getHeight();

	Rect rect(0, 0, getWidth(), fontHeight);

	for(auto&& line : mLines)
	{
		mrefBitmapFont->render(
			renderContext,
			line,
			rect);

		rect.setY(rect.getY() + fontHeight);
	}
}

void Console::addLine(CStr line)
{
	mLines.push_back(std::string(line.c_str()));
}

}
