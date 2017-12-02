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

void Image::resize(const Size& oldSize, const Size& newSize)
{

}

void Image::render(RenderContext& renderContext)
{
	renderContext.draw(
		mrefSurface,
		getRect().getPosition());
}

}
