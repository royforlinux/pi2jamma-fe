#pragma once

#include "ui/device/sdl2/sdl2types.hpp"

class Color
{
public:

	using ElementType = decltype(SDL_Color::r);

	Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 0x00);

	ElementType getRed() const;
	ElementType getGreen() const;
	ElementType getBlue() const;
	ElementType getAlpha() const;

private:
	SDL_Color mSdlColor;

	friend class Application;
};

inline Color::Color(
	ElementType red,
	ElementType green,
	ElementType blue,
	ElementType alpha)
	: mSdlColor({red,green,blue,alpha})
{	
}

inline Color::ElementType Color::getRed() const
{
	return mSdlColor.r;

}

inline Color::ElementType Color::getGreen() const
{
	return mSdlColor.g;

}

inline Color::ElementType Color::getBlue() const
{
	return mSdlColor.b;

}

inline Color::ElementType Color::getAlpha() const
{
	return mSdlColor.a;
}

