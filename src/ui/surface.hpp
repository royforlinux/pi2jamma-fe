#pragma once

#include "result.hpp"

#include <SDL.h>
#include <memory>

class Surface
{
public:
	Surface();

private:

	std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> muptSdlSurface;
	
};