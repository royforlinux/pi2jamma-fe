#pragma once

#include "ui/Elements/Element.hpp"

namespace ui
{

class Console
{
public:

	Console(
		Element* pParent,
		const Rect& rect,
		ref<BitmapFont> refBitmapFont);

private:

	virtual void render(RenderContext& renderContext);

	ref<BitmapFont> mrefBitmapFont;
	std::vector<std::string> mLines;
};

}

