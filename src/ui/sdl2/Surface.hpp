#pragma once

#include "ui/sdl2/Size.hpp"

class Surface
{

public:

	Surface() = default;

	const Size& getSize() const;

private:

	Surface(std::unique_ptr<SDL_Texture> uptSdlTexture);

	Size mSize;
	std::unique_ptr<SDL_Texture> muptSdlTexture;

friend class Application;
};

inline const Size& Surface::getSize() const
{
	return mSize;
}

