#include "ui/Image.hpp"

Image::Image(
	Element* pParent,
	const char* pFilePath)
	: Element(pParent)
{
	Result r = Application::get()->loadSurface(mSurface, pFilePath);
	r.ignore();
}


void Image::render(RenderContext& renderContext)
{
	renderContext.draw(
		mSurface,
		getRect().getPosition());
}
