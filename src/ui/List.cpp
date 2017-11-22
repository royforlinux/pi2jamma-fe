
#include "ui/List.hpp"

List::List(
	Element* pParent,
	ref<Font> refFont,
	const Color& unselectedColor,
	const Color& selectedColor,
	std::vector<std::string> items)
	: Element(pParent)
	, mrefFont(std::move(refFont))
	, mUnselectedColor(unselectedColor)
	, mSelectedColor(selectedColor)
	, mItems(std::move(items))
	, mSelectedItem(-1)
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
}

void List::setSelection(const size_t itemIndex)
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

	setSelection(
		mSelectedItem - 1);
}

void List::down()
{
	if( mSelectedItem < mItems.size() - 1 )
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
	UnitType x = 0;
	UnitType y = 0;

	auto numItems = mLabels.size();

	for(size_t i = 0; i < numItems; i ++ ) {
		auto&& refSurface = mLabels[i];
		Point position(x,y);
		y += refSurface->getHeight();		

		if(mSelectedItem == i) {
			renderContext.draw(mrefSelectedSurface, position);
		}
		else {
			renderContext.draw(refSurface, position);
		}
	}
}
