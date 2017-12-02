
#include "ui/elements/Label.hpp"
#include "ui/Application.hpp"

namespace ui {

Label::Label(
	Element* pParent,
	const Rect& rect,
	ref<Font> refFont,
	const Color& color,
	std::string text)
	: Element(pParent, rect)
	, mrefFont(std::move(refFont))
	, mColor(color)
	, mText(std::move(text))
{
	resize(Size(), rect.getSize());
}


void Label::render(RenderContext& renderContext)
{
	renderContext.draw(
		mrefSurface,
		getRect().getPosition());
}

void Label::resize(const Size& oldSize, const Size& newSize)
{
	Result r =
		Application::get()->renderText(
			mrefSurface,
			mrefFont,
			mColor,
			mText.c_str());
	r.ignore();
}

}

