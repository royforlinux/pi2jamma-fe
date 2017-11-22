#pragma once

#include "ui/Element.hpp"

class Label final : public Element
{
	public:

		Label(
			Element* pParent,
			const Font& font,
			const Color& color,
			const char* text);		

	protected:

		virtual void render(RenderContext& renderContext) override;

	private:

		Surface mSurface;

};