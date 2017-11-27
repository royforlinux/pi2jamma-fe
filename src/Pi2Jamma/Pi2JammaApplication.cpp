#include "Pi2Jamma/Pi2JammaApplication.hpp"

#include "Pi2Jamma/Theme.hpp"
#include "core/meta/Meta.hpp"
#include "core/json/JsonParser.hpp"
#include "core/serialize/Serializer.hpp"

Result Pi2JammaApplication::initialize()
{
	Meta::initialize();
	ui::initialize();
	Theme::initialize();

	mrefBackground =
		make_ref<Image>(
			nullptr,
			"/home/x/arcade/pi2jamma-fe/themes/vertical/burgertime/background.png");

	Result result =
		loadFont(
			mrefFont,
			20,
			"/home/x/arcade/pi2jamma-fe/themes/vertical/burgertime/vgafix.fon");

	if(result.peekFailed()) {
		return result;
	}

	mrefTitle =
		make_ref<Label>(
			nullptr,
			mrefFont,
			Color(0, 0xFF, 0),
			"Title");

	Json json(4);

	result = JsonLoadFromFile(json, "/home/x/arcade/pi2jamma-fe/themes/vertical/burgertime/config.txt");
	if(result.peekFailed()) {
		return result;
	}

	std::string s = json.Stringify();
	LogFmt("load:%s\n", s.c_str());

	Theme theme;
	result = load(theme, json);
	if(result.peekFailed()) {
		return result;
	}


	result = save(theme,json);
	if(result.peekFailed()) {
		return result;
	}

	s = json.Stringify();

	LogFmt("\n\nsave:%s\n", s.c_str());

	LogFmt( "\n\nSnapsRect:%d\n", (int) theme.mSnapsRect.getX());

	std::vector<std::string> items({
		"pacman",
		"dig-dig",
		"ms.pacman",
		"burgertime (Midway) V1",
		"galaxian V1",
		"galaxian V2",
		"galaxian V3",
		"galaxian V5",
		"halo"});

	mrefList =
		make_ref<List>(
			nullptr,
			mrefFont,
			Color(0x80, 0x80, 0x80),
			Color(0xFF, 0x00, 0x00),
			24,
			std::move(items));

	mrefList->setRect(Rect(100, 100, 100, 150));

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
		return;
	}

	if (keyDownEvent.getKey() == Key::DownArrow) {
		mrefList->down();
		return;
	}

	if(keyDownEvent.getKey() == Key::Escape)
	{
		quit();
	}
}
