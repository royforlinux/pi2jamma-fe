#pragma once

#include "ui/Color.hpp"
#include "ui/Font.hpp"
#include "ui/Surface.hpp"
#include "ui/HorizontalAlignment.hpp"
#include "ui/elements/Element.hpp"

#include <vector>

namespace ui {

class List final : public Element
{
public:

	List(
		Element* pParent,
		const Rect& rect,
		ref<Font> refFont,
		const Color& unselectedColor,
		const Color& selectedColor,
		UnitType lineHeight,		
		std::vector<std::string> items,
		HorizontalAlignment = HorizontalAlignment::Center);

	void setSelection(const int itemIndex);

	void up();
	void down();

protected:

	virtual void render(RenderContext& renderContext) override;
	virtual void resize(const Size& oldSize, const Size& newSize) override;

private:

	ref<Surface> createSurface(
		const Color& color,
		const std::string& text);

	ref<Font> mrefFont;
	Color mUnselectedColor;
	Color mSelectedColor;
	UnitType mLineHeight;
	HorizontalAlignment mHorizontalAlignment;

	std::vector<std::string> mItems;
	std::vector<ref<Surface>> mLabels;

	ref<Surface> mrefSelectedSurface;

	int mSelectedItem = -1;
	int mNumItemsToDisplay = 0;
};

}

