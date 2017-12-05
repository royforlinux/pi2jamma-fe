#pragma once

class BitmapFont
{
public:
	static ref<BitmapFont> fromFont(
		ref<Font> refFont,
		const Color& color);

	BitmapFont(ref<Surface> refSurface);

	Size getGlyphSize() const;	

	void Render(
		RenderContext& renderContext,
		StringSpan stringSpan,
		const Rect& rect);

private:

	ref<Surface> mrefSurface;
};