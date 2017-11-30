#pragma once

#include "ui/elements/Element.hpp"

class Label final : public Element
{
public:

	Label(
		Element* pParent,
		const Rect& rect,
		const ref<Font>& refFont,
		const Color& color,
		const char* text);		

protected:

	virtual void render(RenderContext& renderContext) override;
	virtual void resize(const Size& oldSize, const Size& newSize) override;
	
private:

	ref<Surface> mrefSurface;

};
