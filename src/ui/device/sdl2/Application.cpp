#include "ui/device/sdl2/Application.hpp"

Application* Application::spSingleton = nullptr;

Application::Application()
	: mQuit(false)
{
	ASSERT(nullptr == spSingleton);
	spSingleton = this;
}

Application::~Application()
{
	muptSdlRenderer.release();
	muptSdlWindow.release();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	spSingleton = nullptr;
}

Result Application::run()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	if(0 != sdlInitResult) {
		return Result::makeFailureWithString(SDL_GetError());
	}

	int imgInitFlags = IMG_INIT_PNG;
	int imgInitResult = IMG_Init(imgInitFlags);

	if(imgInitFlags != imgInitResult) {
		return Result::makeFailureWithString(IMG_GetError());
	}

	int ttfInitResult = TTF_Init();
	if(0 != ttfInitResult) {
		return Result::makeFailureWithString(TTF_GetError());
	}

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

	muptSdlRenderer.reset(
			SDL_CreateRenderer(
				muptSdlWindow.get(),
				-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	if(!muptSdlRenderer) {
		return Result::makeFailureWithString(SDL_GetError());
	}

	Result result = initialize();
	if (result.peekFailed()) {
		return result;
	}

	return renderLoop();
}

Result Application::renderLoop()
{
	SDL_Event sdlEvent = {};

	while(!mQuit)
	{
		if( 0 != SDL_PollEvent(&sdlEvent))
		{
			dispatchEvent(sdlEvent);
		}

		SDL_RenderClear(muptSdlRenderer.get());
		render();
		SDL_RenderPresent(muptSdlRenderer.get());
	}

	return Result::makeSuccess();
}

Result Application::loadSurface(
	ref<Surface>& refSurface,
	const char* filePath)
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

	refSurface = make_ref<Surface>(std::move(uptSdlTexture));

	return Result::makeSuccess();
}


void Application::draw(
	const ref<Surface>& refSurface,
	const Point& targetPoint)
{
	SDL_Rect dst = {
		targetPoint.getX(),
		targetPoint.getY(),
		refSurface->getSize().getWidth(),
		refSurface->getSize().getHeight() };

	SDL_RenderCopy(
		muptSdlRenderer.get(),
		refSurface->getSdlTexture(),
		nullptr,
		&dst);
}

void Application::drawRect(const Rect& rect, const Color& color)
{
	auto pRenderer = muptSdlRenderer.get();

	auto result =
		SDL_SetRenderDrawColor(
			pRenderer,
			color.getRed(),
			color.getGreen(),
			color.getBlue(),
			color.getAlpha());

	ASSERT(0 == result);

	result =
		SDL_RenderDrawRect(
			pRenderer,
			rect.getSdlRect());

	ASSERT(0 == result);
}


Result Application::loadFont(ref<Font>& refFont, UnitType sizePx, const char* filename)
{
	std::unique_ptr<TTF_Font> uptSdlFont(
		TTF_OpenFont(filename, sizePx));

	if(!uptSdlFont) {
		return Result::makeFailureWithString(TTF_GetError());
	}

	refFont = make_ref<Font>(std::move(uptSdlFont));

	return Result::makeSuccess();
}

Result Application::renderText(
	ref<Surface>& refSurface,
	const ref<Font>& refFont,
	const Color& color,
	const char* text)
{
	std::unique_ptr<SDL_Surface> uptSdlSurface(
		TTF_RenderText_Solid(
			refFont->muptSdlFont.get(),
			text,
			color.mSdlColor));

	if(!uptSdlSurface) {
		return Result::makeFailureWithString(TTF_GetError());
	}

	std::unique_ptr<SDL_Texture> uptSdlTexture(
		SDL_CreateTextureFromSurface(
			muptSdlRenderer.get(),
			uptSdlSurface.get()));

	if(!uptSdlTexture) {
		return Result::makeFailureWithString(SDL_GetError());
	}

	refSurface = make_ref<Surface>(std::move(uptSdlTexture));

	return Result::makeSuccess();
}

void Application::dispatchEvent(const SDL_Event& sdlEvent)
{
	if(SDL_QUIT == sdlEvent.type)
	{
		quit();
	}
	else if (SDL_KEYDOWN == sdlEvent.type)
	{
		keyDownEvent(KeyDownEvent(sdlEvent));
	}
}