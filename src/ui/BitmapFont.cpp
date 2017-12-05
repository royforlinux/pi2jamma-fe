#include "ui/BitmapFont.hpp"

ref<BitmapFont> BitmapFont:fromFont(
	ref<Font> refFont,
	const Color& color)
{
	char c[2];
	c[1] = '\0';

	Size glyphSize(0, 0);

	for(char i = 0; i < 127; i ++)
	{
		c[0] = i;
		Size size;
		refFont->sizeText(c, size);

		glyphSize.setWidth(
			std::max(
				glyphSize.getWidth(),
				size.getWidth()));

		glyphSize.setHeight(
			std::max(
				glyphSize.getHeight(),
				size.getHeight()));

	}

	ref<Surface> refSurface;
	Result r = Application::get().createSurface(
		refSurface,
		Size(
			glyphSize.getWidth() * 16,
			glypSize.getHeight() * 16));

	r.catastrophic();

	for(size_t r = 0; r < 16; r ++ )
	{
		for(size_t c = 0; c < 16; c ++) {

			ref<Surface> refGlyphSurface;

			r =
				Application.renderText(
					refSurface


		}

	Application::renderText

}

BitmapFont::BitmapFont(ref<Surface> refSurface)
	: mrefSurface(std::move(refSurface))
{
}

Size BitmapFont::getGlyphSize() const
{
	return
		Size(
			refSurface->GetHeight() / 16,
			refSurface->GetWidth() / 16);
}

void BitmapFont::Render(
	RenderContext& renderContext,
	StringSpan stringSpan,
	const Rect& rect)
{
}