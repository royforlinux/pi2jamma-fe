#include "Pi2Jamma/Pi2JammaApplication.hpp"

#include "Pi2Jamma/CommandLine/CommandLineHandlerConfigFile.hpp"
#include "Pi2Jamma/Game.hpp"
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
	Game::initialize();
	Games::initialize();

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

	CStr dataDir = "/home/x/arcade/pi2jamma-fe/data";
	std::string themesDir = joinPath(dataDir, "themes");

	const UiConfiguration& uiConfig = mConfiguration.getUi();

	bool portrait =
		(ui::Orientation::Portrait == uiConfig.getScreenOrientation());

	CStr orientationDir =
		portrait
			? "portrait"
			: "landsape";

	CStr themeDir =
		portrait
			? uiConfig.getPortraitTheme()
			: uiConfig.getLandscapeTheme();


	std::string fullThemeDir =
		joinPath(themesDir, orientationDir, themeDir);

	std::string configFilePath = joinPath(fullThemeDir, "config.txt");
	std::string gamesPath = joinPath(dataDir, "games.txt");

	Theme theme;
	result = loadJson(theme, configFilePath.c_str());

	if(result.peekFailed()) {
		return result;
	}

	mrefBackground =
		make_ref<ui::Image>(
			nullptr,
			ui::Rect(0, 0, 240, 320),
			joinPath(fullThemeDir, "background.png"));

	result =
		loadFont(
			mrefFont,
			theme.getMenuTextSize(),
			joinPath(fullThemeDir, theme.getFontFilePath()));

	if(result.peekFailed()) {
		return result;
	}

	Games games;
	result = loadJson(games, gamesPath);
	if(result.peekFailed()) {
		return result;
	}

	mrefTitle =
		make_ref<ui::Label>(
			nullptr,
			theme.getTitleRect(),
			mrefFont,
			theme.getTitleTextColor(),
			"Title",
			theme.getTitleAlignment());

	std::vector<std::string> items;
	for(auto&& game : games.getGameList()) {
		items.push_back(game.getDisplayName());
	}

	items.push_back("Burgertime Midway V1 (RomSet 14)");

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

void Pi2JammaApplication::render(ui::RenderContext& renderContext)
{
	mrefBackground->renderTree(renderContext);
	mrefTitle->renderTree(renderContext);
	mrefList->renderTree(renderContext);
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
