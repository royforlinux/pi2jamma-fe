#pragma once

#include "ui/Surface.hpp"
#include "ui/elements/Element.hpp"

namespace ui {

class Image final : public Element
{
	public:

		Image(
			Element* pParent,
			const Rect& rect,
			CStr filePath);

	protected:

		virtual void render(RenderContext& renderContext) override;

	private:

		ref<ui::Surface> mrefSurface;
};

}