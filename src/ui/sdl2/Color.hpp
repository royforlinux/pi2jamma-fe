#pragma once

#include "ui/sdl2/sdl2types.hpp"

class Color
{
	private:
		SDL_Color mSdlColor;

	friend class Application;
};