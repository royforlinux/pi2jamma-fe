
#include "ui/Label.hpp"

Label::Label(
	Element* pParent,
	const Font& font,
	const Color& color,
	const char* text)
	: Element(pParent)
{
	Result r = Application::get()->renderText(mSurface, font, color, text);
	r.ignore();
}


void Label::render(RenderContext& renderContext)
{
	renderContext.draw(
		mSurface,
		getRect().getPosition());
}
