
#include "ui/elements/Label.hpp"

Label::Label(
	Element* pParent,
	const ref<Font>& refFont,
	const Color& color,
	const char* text)
	: Element(pParent)
{
	Result r = Application::get()->renderText(mrefSurface, refFont, color, text);
	r.ignore();
}


void Label::render(RenderContext& renderContext)
{
	renderContext.draw(
		mrefSurface,
		getRect().getPosition());
}

void Label::resize(const Size& oldSize, const Size& newSize)
{
}

