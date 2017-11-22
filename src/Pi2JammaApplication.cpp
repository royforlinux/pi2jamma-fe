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

	result =
		renderText(
			mTitle,
			mFont,
			Color(),
			"Title");

	if(result.peekFailed()) {
		return result;
	}

	return Result::makeSuccess();
}

void Pi2JammaApplication::render()
{
	draw(mBackground, Point(0,0));
	draw(mTitle, Point(0,0));
}
