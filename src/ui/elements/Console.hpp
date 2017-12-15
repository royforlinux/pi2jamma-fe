#pragma once

#include "ui/BitmapFont.hpp"
#include "ui/elements/Element.hpp"

#include "core/log/Log.hpp"

#include <vector>

namespace ui {

class Console : public Element
{
public:

	Console(
		Element* pParent,
		const Rect& rect,
		ref<BitmapFont> refBitmapFont);

	void clear();

protected:

	class ConsoleLogHandler : public LogHandler
	{
	public:
		ConsoleLogHandler(Console& console);

		virtual void log(CStr line) override;
	private:
		Console& mConsole;
	};

	void addLine(CStr line);

	virtual void render(RenderContext& renderContext) override;

	ConsoleLogHandler mLogHandler;
	ref<BitmapFont> mrefBitmapFont;
	std::vector<std::string> mLines;
};

}