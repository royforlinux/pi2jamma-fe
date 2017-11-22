#include "ui/surface.hpp"

#include "debug.hpp"

Surface::Surface(std::unique_ptr<SDL_Texture> uptSdlTexture)
	: muptSdlTexture(std::move(uptSdlTexture))
{
	UnitType width;
	UnitType height;

	int result =
		SDL_QueryTexture(
			muptSdlTexture.get(),
			nullptr,
			nullptr,
			& width,
			& height);

	mSize = Size(width, height);

	ASSERT(0 == result);
}
