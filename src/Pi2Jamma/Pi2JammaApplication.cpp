#include "Pi2Jamma/Pi2JammaApplication.hpp"

#include "Pi2Jamma/CommandLine/CommandLineHandlerConfigFile.hpp"
#include "Pi2Jamma/Theme.hpp"
#include "core/file/FilePath.hpp"
#include "core/meta/Meta.hpp"
#include "core/json/JsonParser.hpp"
#include "core/serialize/json/JsonSerialize.hpp"
#include "core/CommandLine/CommandLine.hpp"
#include "ui/ui.hpp"

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

	result = loadJson(
		mConfiguration,
		CommandLineHandlerConfigFile::sSingleton.mConfigFile);



	if(result.peekFailed()) {
		return result;
	}
	
	std::string d = dump(mConfiguration);
	LogFmt("%s\n", d.c_str());

	const char* pThemesDir = "/home/x/arcade/pi2jamma-fe/data/themes";
	const char* pThemeDir = "vertical/burgertime";

	std::string s = joinPath({pThemesDir, pThemeDir, "config.txt" });

	Theme theme;
	result = loadJson(theme, s.c_str());

	if(result.peekFailed()) {
		return result;
	}

	d = dump(theme);
	LogFmt("%s\n", d.c_str());

	mrefBackground =
		make_ref<ui::Image>(
			nullptr,
			ui::Rect(0, 0, 240, 320),
			"/home/x/arcade/pi2jamma-fe/data/themes/vertical/burgertime/background.png");

	result =
		loadFont(
			mrefFont,
			theme.getMenuTextSize(),
			"/home/x/arcade/pi2jamma-fe/data/themes/vertical/burgertime/vgafix.fon");

	if(result.peekFailed()) {
		return result;
	}

	mrefTitle =
		make_ref<ui::Label>(
			nullptr,
			theme.getTitleRect(),
			mrefFont,
			theme.getTitleTextColor(),
			"Title");

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
		make_ref<ui::List>(
			nullptr,
			theme.getMenuRect(),
			mrefFont,
			theme.getMenuTextColor(),
			theme.getMenuTextHighlightColor(),
			theme.getMenuTextSize(),
			std::move(items));

	return Result::makeSuccess();
}

void Pi2JammaApplication::render()
{
	mrefBackground->renderTree(*this);
	mrefTitle->renderTree(*this);
	mrefList->renderTree(*this);
}

void Pi2JammaApplication::keyDownEvent(const ui::KeyDownEvent& keyDownEvent)
{
	if (keyDownEvent.getKey() == ui::Key::UpArrow) {
		mrefList->up();
		return;
	}

	if (keyDownEvent.getKey() == ui::Key::DownArrow) {
		mrefList->down();
		return;
	}

	if(keyDownEvent.getKey() == ui::Key::Escape)
	{
		quit();
	}
}
