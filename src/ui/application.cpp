#include "ui/application.hpp"

#include <SDL.h>

Application::Application()
{
}

Application::~Application()
{
	SDL_Quit();
}

Result Application::initialize()
{
	auto result = SDL_Init(SDL_INIT_VIDEO);

	if(0 != result) {

		return Result::makeFailureWithString(SDL_GetError());
	}

	Log("Initialized SDL2");

	SDL_Window* pSdlWindow =
		SDL_CreateWindow(
			"My Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			SDL_WINDOW_SHOWN);

	if(nullptr == pSdlWindow) {
		return Result::makeFailureWithString(SDL_GetError());
	}

	mWindow = Window(pSdlWindow);

	return Result::makeSuccess();
}

Result Application::run()
{
	SDL_Delay(1000);

	return Result::makeSuccess();
}
