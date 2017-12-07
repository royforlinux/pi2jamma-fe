#pragma once

#include "ui/elements/Element.hpp"
#include "ui/BitmapFont.hpp"

class MenuScreen : public ui::Element
{
public:
	MenuScreen(
		ui::Element* pParent,
		const ui::Rect& rect,
		ref<ui::BitmapFont> refBitmapFont);

private:
	ref<ui::BitmapFont> mrefBitmapFont;
};
