
#include "ui/elements/List.hpp"

#include "ui/Application.hpp"
#include "ui/Point.hpp"

namespace ui {

List::List(
	Element* pParent,
	const Rect& rect,
	ref<Font> refFont,
	const Color& unselectedColor,
	const Color& selectedColor,
	UnitType lineHeight,
	std::vector<std::string> items,
	HorizontalAlignment horizontalAlignment)
	: Element(pParent, rect)
	, mrefFont(std::move(refFont))
	, mUnselectedColor(unselectedColor)
	, mSelectedColor(selectedColor)
	, mLineHeight(lineHeight)
	, mHorizontalAlignment(horizontalAlignment)	
	, mItems(std::move(items))
{
	mLabels.reserve(mItems.size());
	
	for(auto&& s : mItems)
	{
		ref<Surface> refSurface;

		mLabels.emplace_back(
			createSurface(
				mUnselectedColor,
				s));
	}

	if(mItems.size() > 0 ) {
		setSelection(0);
	}

	resize(Size(0,0), rect.getSize());
}

void List::setSelection(const int itemIndex)
{
	if(itemIndex == mSelectedItem) {
		return;
	}

	mSelectedItem = itemIndex;

	mrefSelectedSurface =
		createSurface(
			mSelectedColor,
			mItems[mSelectedItem]);
}

void List::up()
{
	if (mSelectedItem <= 0 ) {
		return;
	}

	setSelection(mSelectedItem - 1);
}

void List::down()
{
	if( mSelectedItem < static_cast<int>(mItems.size()) - 1 )
	{
		setSelection(mSelectedItem + 1);
	}

}

ref<Surface> List::createSurface(
	const Color& color,
	const std::string& text)
{
	ref<Surface> refSurface;

	Result r =
		Application::get()->renderText(
			refSurface,
			mrefFont,
			color,
			text.c_str());

	r.ignore();

	return refSurface;
}


void List::render(RenderContext& renderContext)
{
	UnitType centerY = getRect().getYCenter();

	UnitType x = getX();
	UnitType y = centerY - (mLineHeight/2);
	y -= ((mNumItemsToDisplay / 2) * mLineHeight);

	int numItems = mLabels.size();

	int firstItemToDisplay = mSelectedItem - (mNumItemsToDisplay / 2);
	int lastItemToDisplay = firstItemToDisplay + mNumItemsToDisplay;

	for(int i = firstItemToDisplay; i < lastItemToDisplay; i ++ ) 
	{
		Point position(x,y);
		y += mLineHeight;

		if (i < 0) {
			continue;
		}

		if(i >= numItems) {
			break;
		}

		auto refSurface = mLabels[i];

		if(i == mSelectedItem) {
			refSurface = mrefSelectedSurface;
		}

		renderContext.draw(
			refSurface,
			position);
	}
}

void List::resize(const Size& oldSize, const Size& newSize)
{
	mNumItemsToDisplay = newSize.getHeight() / mLineHeight;

	if(0 ==(mNumItemsToDisplay %2)) {
		mNumItemsToDisplay--;
	}

	mNumItemsToDisplay = std::max(mNumItemsToDisplay, 1);
}

}

