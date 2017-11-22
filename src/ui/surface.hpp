#pragma once

#include "ui/sdl2/Size.hpp"

class Surface
{

public:

	Surface() = default;

	Surface(
		std::unique_ptr<SDL_Texture> uptSdlTexture);

	const Size& getSize() const;

private:

	Size mSize;
	std::unique_ptr<SDL_Texture> muptSdlTexture;

friend class Application;
};

inline const Size& Surface::getSize() const
{
	return mSize;
}

