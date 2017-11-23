#include "ui/elements/Image.hpp"

Image::Image(
	Element* pParent,
	const char* pFilePath)
	: Element(pParent)
{
	Result r = Application::get()->loadSurface(mrefSurface, pFilePath);
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