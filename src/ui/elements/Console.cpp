#include 'ui/elements/Console.hpp'

Console::Console(
	Element* pParent,
	const Rect& rect,
	ref<BitmapFont> refBitmapFont)
	: Element(
		pParent,
		rect)
{
}

void Console::render(RenderContext& renderContext)
{
	auto fontHeight = refBitmapFont->getHeight();
	auto possibleLines = getHeight() / fontHeight;
	auto numLinesInBuffer = mLines.size();
	auto numLinesToShow = std::min(numLinesInBuffer, possibleLines);
	auto startLine = numLinesInBuffer - numLinesToShow;

	UnitType x = 0;
	for(size_t i = 0; i < numLinesToShow; i ++)
	{
		auto&& line = mLines[i + startLine];
		mrefBitmapFont->draw(renderContext, line);
	}
}


