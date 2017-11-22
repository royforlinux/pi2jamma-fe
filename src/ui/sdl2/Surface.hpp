#pragma once

#include "ui/sdl2/Size.hpp"
#include "core/RefCounted.hpp"

class Surface : public RefCounted
{

public:

	Surface() = default;
	Surface(std::unique_ptr<SDL_Texture> uptSdlTexture);	

	const Size& getSize() const;

	UnitType getWidth() const;
	UnitType getHeight() const;

private:

	Size mSize;
	std::unique_ptr<SDL_Texture> muptSdlTexture;

friend class Application;
};

inline const Size& Surface::getSize() const
{
	return mSize;
}

inline UnitType Surface::getWidth() const
{
	return mSize.getWidth();
}

inline UnitType Surface::getHeight() const
{
	return mSize.getHeight();
}

