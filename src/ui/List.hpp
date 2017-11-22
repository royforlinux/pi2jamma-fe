#pragma once

#include "ui/Element.hpp"

class List final : public Element
{
public:

	List(
		Element* pParent,
		ref<Font> refFont,
		const Color& unselectedColor,
		const Color& selectedColor,
		std::vector<std::string> items);

	void setSelection(const size_t itemIndex);

	void up();
	void down();

protected:

	virtual void render(RenderContext& renderContext) override;

private:

	ref<Surface> createSurface(
		const Color& color,
		const std::string& text);

	ref<Font> mrefFont;
	Color mUnselectedColor;
	Color mSelectedColor;

	std::vector<std::string> mItems;
	std::vector<ref<Surface>> mLabels;

	ref<Surface> mrefSelectedSurface;

	size_t mSelectedItem;
};

