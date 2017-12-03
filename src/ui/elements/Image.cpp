#include "ui/elements/Image.hpp"
#include "ui/Application.hpp"

namespace ui {

Image::Image(
	Element* pParent,
	const Rect& rect,
	CStr filePath)
	: Element(pParent, rect)
{
	Result r = Application::get().loadSurface(mrefSurface, filePath);
	r.ignore();
}

void Image::render(RenderContext& renderContext)
{
	if(mrefSurface.isNull()) {
		return;
	}
	renderContext.draw(
		mrefSurface,
		getRect().getPosition());
}

}
