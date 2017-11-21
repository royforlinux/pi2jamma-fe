#include "ui/surface.hpp"

Surface::Surface()
	: muptSdlSurface(nullptr, & SDL_FreeSurface)
{

}