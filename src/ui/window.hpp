#pragma once

#include <SDL.h>
#include <memory>

class Window
{
	Window& operator=(const Window& rhs) = delete;
	Window& operator=(Window&& rhs);
	~Window();
	
private:

	Window(SDL_Window* pSdlWindow = nullptr);

	SDL_Window* mpSdlWindow;

friend class Application;
};
