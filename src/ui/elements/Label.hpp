#pragma once

#include "ui/elements/Element.hpp"
#include "ui/Color.hpp"
#include "ui/Font.hpp"
#include "ui/Surface.hpp"

namespace ui {

class Label final : public Element
{
public:

	Label(
		Element* pParent,
		const Rect& rect,
		ref<Font> refFont,
		const Color& color,
		std::string text);		

protected:

	virtual void render(RenderContext& renderContext) override;
	virtual void resize(const Size& oldSize, const Size& newSize) override;
	
private:

	ref<Surface> mrefSurface;
	ref<Font> mrefFont;
	Color mColor;
	std::string mText;
};

}
