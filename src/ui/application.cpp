#include "ui/application.hpp"

Application::Application()
	: mQuit(false)
{
}

Application::~Application()
{
	muptSdlRenderer.release();
	muptSdlWindow.release();

	IMG_Quit();
	SDL_Quit();
}

Result Application::run()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);

	if(0 != sdlInitResult) {

		return Result::makeFailureWithString(SDL_GetError());
	}

	Log("SDL_Init");

	int imgInitFlags = IMG_INIT_PNG;
	int imgInitResult = IMG_Init(imgInitFlags);

	if(imgInitFlags != imgInitResult) {
		return Result::makeFailureWithString(IMG_GetError());
	}

	Log("IMG_Init");

	muptSdlWindow.reset(
		SDL_CreateWindow(
			"My Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640,
			480,
			SDL_WINDOW_SHOWN));

	if(!muptSdlWindow) {
		return Result::makeFailureWithString(SDL_GetError());
	}

	Log("SDL_CreateWindow");

	muptSdlRenderer.reset(
			SDL_CreateRenderer(
				muptSdlWindow.get(),
				-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	if(!muptSdlRenderer) {
		return Result::makeFailureWithString(SDL_GetError());
	}

	Log("SDL_CreateRenderer");

	Result result = initialize();
	if (result.peekFailed()) {
		return result;
	}

	return renderLoop();
}

Result Application::renderLoop()
{
	//while(!mQuit)
	{
		SDL_RenderClear(muptSdlRenderer.get());
		render();
		SDL_RenderPresent(muptSdlRenderer.get());
		SDL_Delay(1000);	
	}

	return Result::makeSuccess();
}

Result Application::loadSurface(Surface& surface, const char* filePath)
{
	ASSERT(nullptr != filePath);

	std::unique_ptr<SDL_Texture> uptSdlTexture(
		IMG_LoadTexture(
			muptSdlRenderer.get(),
			filePath));

	if(!uptSdlTexture) {
		LogFmt( "Failed to load texture: %s\n", filePath);		
		return Result::makeFailureWithString(IMG_GetError());
	}

	surface = Surface(std::move(uptSdlTexture));

	return Result::makeSuccess();
}


void Application::draw(Surface& surface, const Point& targetPoint){
	SDL_Rect dst = {
		targetPoint.getX(),
		targetPoint.getY(),
		surface.getSize().getWidth(),
		surface.getSize().getHeight() };

	SDL_RenderCopy(
		muptSdlRenderer.get(),
		surface.muptSdlTexture.get(),
		nullptr,
		&dst);


}