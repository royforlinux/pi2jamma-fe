#include "Pi2JammaApplication.hpp"

Result Pi2JammaApplication::initialize()
{
	mrefBackground =
		make_ref<Image>(
			nullptr,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/background.png");

	Result result =
		loadFont(
			mFont,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/ARCADECLASSIC.TTF");

	if(result.peekFailed()) {
		return result;
	}

	mrefTitle =
		make_ref<Label>(
			nullptr,
			mFont,
			Color(0, 0xFF, 0),
			"Title");

	return Result::makeSuccess();
}

void Pi2JammaApplication::render()
{
	mrefBackground->renderTree(*this);
	mrefTitle->renderTree(*this);
}

void Pi2JammaApplication::keyDownEvent(const KeyDownEvent& keyDownEvent)
{
	quit();
}
