#include "ui/window.hpp"

Window::Window(SDL_Window* pSdlWindow)
	: mpSdlWindow(pSdlWindow)
{
}

Window& Window::operator=(Window&& rhs)
{
	if(nullptr != mpSdlWindow)
	{
		SDL_DestroyWindow(mpSdlWindow);
	}

	mpSdlWindow = rhs.mpSdlWindow;
	rhs.mpSdlWindow = nullptr;

	return *this;
}

Window::~Window()
{
	if(nullptr == mpSdlWindow)
	{
		return;
	}

	SDL_DestroyWindow(mpSdlWindow);
}
