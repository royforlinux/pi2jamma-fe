#include "Pi2Jamma/screens/MenuScreen.hpp"

MenuScreen::MenuScreen(
	ui::Element* pParent,
	const ui::Rect& rect,
	ref<ui::BitmapFont> refBitmapFont)
	: ui::Element(
		pParent,
		rect)
	, mrefBitmapFont(std::move(refBitmapFont))
{
}