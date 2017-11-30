#include "Pi2Jamma/Pi2JammaApplication.hpp"

#include "Pi2Jamma/CommandLine/CommandLineHandlerConfigFile.hpp"
#include "Pi2Jamma/Theme.hpp"
#include "core/file/FilePath.hpp"
#include "core/meta/Meta.hpp"
#include "core/json/JsonParser.hpp"
#include "core/serialize/Serializer.hpp"
#include "core/CommandLine/CommandLine.hpp"

Result Pi2JammaApplication::initialize(int argc, const char* argv[])
{
	Meta::initialize();
	ui::initialize();
	Configuration::initialize();
	Theme::initialize();

	Result result = CommandLine::get().parse(argc, argv);
	if(result.peekFailed()) {
		return result;
	}

	result = load(mConfiguration, CommandLineHandlerConfigFile::sSingleton.mConfigFile);
	if(result.peekFailed()) {
		return result;
	}

	const char* pThemesDir = "/home/x/arcade/pi2jamma-fe/data/themes";
	const char* pThemeDir = "vertical/burgertime";

	std::string s = joinPath({pThemesDir, pThemeDir, "config.txt" });

	Theme theme;
	result = load(theme, s.c_str());

	if(result.peekFailed()) {
		return result;
	}

	mrefBackground =
		make_ref<Image>(
			nullptr,
			"/home/x/arcade/pi2jamma-fe/data/themes/vertical/burgertime/background.png");

	result =
		loadFont(
			mrefFont,
			theme.mMenuTextSize,
			"/home/x/arcade/pi2jamma-fe/data/themes/vertical/burgertime/vgafix.fon");

	if(result.peekFailed()) {
		return result;
	}

	mrefTitle =
		make_ref<Label>(
			nullptr,
			mrefFont,
			theme.mTitleTextColor,
			"Title");

	mrefTitle->setRect(theme.mTitleRect);

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
			theme.mMenuTextColor,
			theme.mMenuTextHighlightColor,
			theme.mMenuTextSize,
			std::move(items));

	mrefList->setRect(theme.mMenuRect);

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
