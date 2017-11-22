#include "Pi2JammaApplication.hpp"

Result Pi2JammaApplication::initialize()
{
	mrefBackground =
		make_ref<Image>(
			nullptr,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/background.png");

	Result result =
		loadFont(
			mrefFont,
			"/home/x/arcade/pi2jamma-fe/themes/burgertime/ARCADECLASSIC.TTF");

	if(result.peekFailed()) {
		return result;
	}

	mrefTitle =
		make_ref<Label>(
			nullptr,
			mrefFont,
			Color(0, 0xFF, 0),
			"Title");

	std::vector<std::string> items( { "pacman", "dig-dig", "ms.pacman"});

	mrefList =
		make_ref<List>(
			nullptr,
			mrefFont,
			Color(0x80, 0x80, 0x80),
			Color(0xFF, 0x00, 0x00),
			std::move(items));

	return Result::makeSuccess();
}

void Pi2JammaApplication::render()
{
	mrefBackground->renderTree(*this);
	mrefTitle->renderTree(*this);
	mrefList->renderTree(*this);
}

void Pi2JammaApplication::keyDownEvent(const KeyDownEvent& keyDownEvent)
{
	if (keyDownEvent.getKey() == Key::UpArrow) {
		mrefList->up();
		Log("up\n");
		return;
	}

	if (keyDownEvent.getKey() == Key::DownArrow) {
		mrefList->down();
		Log("down\n");
		return;
	}

	quit();
}
