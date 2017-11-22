#include "Pi2JammaApplication.hpp"

Result Pi2JammaApplication::initialize()
{
	Result result =
		loadSurface(
			mBackground,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/background.png");

	if(result.peekFailed()) {
		return result;
	}

	result =
		loadFont(
			mFont,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/ARCADECLASSIC.TTF");

	if(result.peekFailed()) {
		return result;
	}

	muptTitle =
		std::make_unique<Label>(
			nullptr,
			mFont,
			Color(0, 0xFF, 0),
			"Title");

	return Result::makeSuccess();
}

void Pi2JammaApplication::render()
{
	draw(mBackground, Point(0,0));
	muptTitle->renderTree(*this);
}

void Pi2JammaApplication::keyDownEvent(const KeyDownEvent& keyDownEvent)
{
	quit();
}
