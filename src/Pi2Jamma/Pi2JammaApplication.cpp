#include "Pi2Jamma/Pi2JammaApplication.hpp"

#include "Pi2Jamma/CommandLine/CommandLineHandlerConfigFile.hpp"
#include "Pi2Jamma/Theme.hpp"
#include "Pi2Jamma/screens/GameSelectScreen.hpp"

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

	result = loadConfiguration();
	if(result.peekFailed()) {
		return result;
	}

	return setupUi();
}

Result Pi2JammaApplication::loadConfiguration()
{
	Result result = loadJson(
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

	mSnapsDir = joinPath(dataDir, "snaps", orientationDir);			

	// Load theme

	mFullThemeDir =
		joinPath(themesDir, orientationDir, themeDir);

	// Load Games

	std::string gamesPath = joinPath(dataDir, "games.txt");

	result = loadJson(mGames, gamesPath);
	if(result.peekFailed()) {
		return result;
	}

	return Result::makeSuccess();
}
Result Pi2JammaApplication::setupUi()
{
	mrefRootElement =
		make_ref<GameSelectScreen>(
			*this,
			mGames,
			mFullThemeDir,
			mSnapsDir);

	return Result::makeSuccess();
}

void Pi2JammaApplication::render(ui::RenderContext& renderContext)
{
	mrefRootElement->renderTree(renderContext);
}

void Pi2JammaApplication::keyDownEvent(const ui::KeyDownEvent& keyDownEvent)
{

	if(keyDownEvent.getKey() == ui::Key::Escape)
	{
		quit();
	}

	ui::InputEvent inputEvent;

	const KeyConfiguration& keyConfig = mConfiguration.getKeys();

	if (keyDownEvent.getKey() == keyConfig.getUp()) {
		inputEvent.setAction(ui::Action::Up);
	} 
	else if (keyDownEvent.getKey() == keyConfig.getDown()) {
		inputEvent.setAction(ui::Action::Down);
	}
	else if(keyDownEvent.getKey() == keyConfig.getSelect()) {
		inputEvent.setAction(ui::Action::Select);
	}

	mrefRootElement->inputEvent(inputEvent);
}
