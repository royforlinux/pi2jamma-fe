#pragma once

#include "ui/sdl2/sdl2types.hpp"

class Color
{
public:

	Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 0x00);

private:
	SDL_Color mSdlColor;

	friend class Application;
};

inline Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	: mSdlColor({red,green,blue,alpha})
{	
}
